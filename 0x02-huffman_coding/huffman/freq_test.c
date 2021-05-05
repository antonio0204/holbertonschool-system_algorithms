#include "huffman.h"
/* malloc */
#include <stdlib.h>

#include <stdio.h>

/* access */
#include <unistd.h>
/* strlen */
#include <string.h>
#include <errno.h>
/*
bit addressible type
*/
typedef struct bit_s {
	size_t byte_idx;
	unsigned char byte;
	unsigned int bit_idx;
} bit_t;

/* pads out to 12 bytes if not `__attribute__((packed))` */
/* maybe short int for offset byte? serialized tree can't be that big for non-Unicode */
/*
typedef struct huffman_header_s {
	unsigned char huff_id[4];
	unsigned int hc_byte_offset;
	unsigned char hc_first_bit_i;
	unsigned char hc_last_bit_i;
} __attribute__((packed)) huffman_header_t;
*/
typedef struct huffman_header_s {
	unsigned char huff_id[4];
	unsigned short int hc_byte_offset;
	unsigned char hc_first_bit_i;
	unsigned char hc_last_bit_i;
} huffman_header_t;

#define BUF_SIZE 1000

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));

/**
 * symbol_print - Prints a symbol structure
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: Number of bytes written in buffer
 */
int symbol_print(char *buffer, void *data)
{
    symbol_t *symbol;
    char c;
    int length;

    symbol = (symbol_t *)data;
    c = symbol->data;
    if (c == -1)
        c = '$';
    length = sprintf(buffer, "(%c/%lu)", c, symbol->freq);
    return (length);
}





/**
 * char_print - prints a char
 *
 * @buffer: Buffer to print into
 * @data: Pointer to a node's data
 *
 * Return: TBD
 */
int char_print(char *buffer, void *data)
{
    char c;
    int length;

    if (data)
	    c = *((char *)data);
    else
	    c = '$';

    if (c < ' ' || c > '~')
	    length = sprintf(buffer, "(%o)", c);
    else
	    length = sprintf(buffer, "(%c)", c);


    return (length);
}



int readBit(unsigned char *buff, bit_t *r_bit, unsigned char *value)
{
	if (!buff || !r_bit || !value)
		return (1);

	printf("\t\tr_bit->byte_idx:%lu r_bit->bit_idx:%u\n", r_bit->byte_idx, r_bit->bit_idx);

	r_bit->byte = buff[r_bit->byte_idx];

	if (r_bit->byte & (1 << (7 - r_bit->bit_idx)))
		*value = 1;
	else
		*value = 0;

	r_bit->bit_idx++;
	if (r_bit->bit_idx == 8)
	{
		r_bit->byte_idx++;
		r_bit->bit_idx = 0;
	}

	return (0);
}

int readByte(unsigned char *buff, bit_t *r_bit, unsigned char *byte)
{
	size_t i;
	unsigned char bit_value;

	if (!buff || !r_bit || !byte)
		return (1);

	printf("\t\t\treadByte start\n");

	for (i = 0; i < 8; i++)
	{
		if (readBit(buff, r_bit, &bit_value) == 1)
			return (1);

		if (bit_value)
			*byte |= (1 << (7 - i));
		else
		        *byte &= ~(1 << (7 - i));
	}

	printf("\t\t\treadByte stop\n");

	return (0);
}


int writeBit(unsigned char *buff, bit_t *w_bit, unsigned char toggle)
{
	if (!buff || !w_bit || (toggle != 0 && toggle != 1))
		return (1);

	if (toggle)
		w_bit->byte |= (1 << (7 - w_bit->bit_idx));
	else
		w_bit->byte &= ~(1 << (7 - w_bit->bit_idx));
	w_bit->bit_idx++;

	if (w_bit->bit_idx == 8)
	{
		buff[w_bit->byte_idx] = w_bit->byte;
		w_bit->byte_idx++;
		w_bit->byte = 0;
		w_bit->bit_idx = 0;
	}

	return (0);
}

int writeByte(unsigned char *buff, bit_t *w_bit, unsigned char byte)
{
	size_t i;

	if (!buff || !w_bit)
		return (1);

	for (i = 0; i < 8; i++)
	{
		if (writeBit(buff, w_bit, (byte & (1 << (7 - i))) ? 1 : 0) == 1)
			return (1);
	}

	return (0);
}


int writePartialByte(unsigned char *buff, bit_t *w_bit)
{
	unsigned int orig_bit_i;

	if (!buff || !w_bit)
		return (1);

	if (w_bit->bit_idx != 0)
	{
		orig_bit_i = w_bit->bit_idx;
		w_bit->bit_idx = 0;
		/* zero-padded by unassigned bits at end */
		writeByte(buff, w_bit, w_bit->byte);
		/* reset to original values */
		w_bit->bit_idx = orig_bit_i;
		w_bit->byte_idx -= 1;
	}

	return (0);
}


void huffmanSerialization(binary_tree_node_t *huffman_tree, unsigned char *buff, bit_t *w_bit)
{
	if (!huffman_tree || !buff || !w_bit)
		return;

	if (!huffman_tree->left && !huffman_tree->right)
	{
		writeBit(buff, w_bit, 1);
		writeByte(buff, w_bit,
			  ((symbol_t *)(huffman_tree->data))->data);
		return;
	}

	writeBit(buff, w_bit, 0);

	huffmanSerialization(huffman_tree->left, buff, w_bit);
	huffmanSerialization(huffman_tree->right, buff, w_bit);
}


binary_tree_node_t *huffmanDeserialization(unsigned char *buff, bit_t *r_bit, binary_tree_node_t *parent)
{
	binary_tree_node_t *new = NULL;
	unsigned char bit, *c = NULL;

	if (!buff || !r_bit)
		return (NULL);

	readBit(buff, r_bit, &bit);

	if (bit == 1)
	{
		c = malloc(sizeof(unsigned char));
		if (!c)
			return (NULL);
		readByte(buff, r_bit, c);
		new = binary_tree_node(parent, c);
		return (new);
	}

	new = binary_tree_node(parent, NULL);
	new->left = huffmanDeserialization(buff, r_bit, new);
	new->right = huffmanDeserialization(buff, r_bit, new);

	return (new);
}



/* write: "01f001c1d01e01a1b" */
int huffmanCompress(char *in_file, char *out_file)
{
	unsigned char buff[BUF_SIZE] = {0};
	FILE *infile = NULL, *outfile = NULL;
	bit_t w_bit = {0, 0, 0};
	huffman_header_t header = {"\177HUF", 0, 0, 0};
	size_t freqs[256] = {0};
	size_t i, j, read_bytes, freq_size, *freq = NULL;
	char *data = NULL;
	binary_tree_node_t *h_tree = NULL;
	bit_t r_bit = {0, 0, 0};

	/* stat for normal file? */
        infile = fopen(in_file, "r");
	if (!infile)
		return (1);

        outfile = fopen(out_file, "w");
	if (!outfile)
	{
		fclose(infile);
		return (1);
	}

	/* build frequency tallies */
        do {
		read_bytes = fread(buff, sizeof(unsigned char), BUF_SIZE, infile);
		printf("\tread_bytes:%lu\n", read_bytes);
		for (i = 0; i < read_bytes; i++)
			freqs[buff[i]]++;
	} while (read_bytes == BUF_SIZE);
	if (!feof(infile)) /* close and cleanup */
		return (1);

	fclose(infile);

	/* no need to sort, heap insertion will sort freqs */
	for (i = 0, freq_size = 0; i < 256; i++)
		if (freqs[i])
			freq_size++;
	data = malloc(sizeof(char) * freq_size);
	if (!data) /* close and cleanup */
		return (1);
	freq = malloc(sizeof(size_t) * freq_size);
	if (!freq) /* close and cleanup */
		return (1);

	for (i = 0, j = 0; i < 256 && j < freq_size; i++)
	{
		if (freqs[i])
		{
			freq[j] = freqs[i];
			data[j] = (char)i;
			j++;
		}
	}

	for (i = 0; i < freq_size; i++)
	{
		if (data[i] < ' ' || data[i] > '~')
			printf("\ti:%lu data:%x freq:%lu", i, data[i], freq[i]);
		else
			printf("\ti:%lu data:'%c' freq:%lu", i, data[i], freq[i]);
		if (i % 2)
			putchar('\n');
	}

	h_tree = huffman_tree(data, freq, freq_size);
	binary_tree_print(h_tree, symbol_print);

        memset(buff, 0, BUF_SIZE);

	huffmanSerialization(h_tree, buff, &w_bit);
	/* if partial byte reamins, write to last byte in buffer */
	if (writePartialByte(buff, &w_bit))
	    return (1);

	binaryTreeDelete(h_tree, freeSymbol);
	h_tree = NULL;

	h_tree = huffmanDeserialization(buff, &r_bit, NULL);
	if (h_tree)
		binary_tree_print(h_tree, char_print);


	/* huffman code starts at bit after serialized tree */
	header.hc_byte_offset = sizeof(huffman_header_t) + w_bit.byte_idx;
        header.hc_first_bit_i = w_bit.bit_idx;
	/* final bit index unknown until codes are written, 0 for now */

	/* write header to file */
        if (fwrite(&header, sizeof(huffman_header_t), 1, outfile) != 1)
		return (1);

	/* write serialized tree to file */
        if (fwrite(buff, sizeof(unsigned char), w_bit.byte_idx + 1, outfile) !=
	    w_bit.byte_idx + 1)
		return (1);

	fclose(outfile);

	return (0);
}

/* read: "01f001c1d01e01a1b" */
int huffmanDecompress(char *in_file, char *out_file)
{
	unsigned char buff[50] = {0};
	FILE *infile = NULL/*, *outfile = NULL*/;
	bit_t r_bit = {0, 0, 0};
	unsigned char bit, symbol;

	(void)out_file;
        infile = fopen(in_file, "r");
	if (!infile)
		return (1);

	if (fread(buff, sizeof(unsigned char), 50, infile) < 50)
		if (!feof(infile))
			return (1);
	fclose(infile);

	printf("read from file: \"");

        readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	readBit(buff, &r_bit, &bit);
	putchar(bit + '0');
	readByte(buff, &r_bit, &symbol);
	putchar(symbol);

	putchar('"');
	putchar('\n');

	return (0);
}


/* no need for envp? locale should have no impact on sorting ASCII */
/* do we need to handle Unicode? */
int main(int argc, char *argv[])
{
	if (argc != 4 ||
	    strlen(argv[1]) != 1 ||
	    (argv[1][0] != 'c' && argv[1][0] != 'd'))
	{
/*
		for (i = 0; i < argc; i++)
			printf("%i:%s\n", i, argv[i]);

		printf("strlen(argv[1]):%lu\n", strlen(argv[1]));
*/
		printf("Usage: huffman <mode> <filename> <out_filename>\n");
		return (1);
	}

	if (access(argv[2], F_OK | R_OK) == -1)
	{
		switch (errno)
		{
		case ENOENT:
			printf("No such file: %s\n", argv[2]);
			break;
		case EACCES:
			printf("No read permission for file: %s\n", argv[2]);
			break;
		default:
		        printf("Cannot access file: %s", argv[2]);
			break;
		}
		return (0);
	}

	if (argv[1][0] == 'c')
		return (huffmanCompress(argv[2], argv[3]));

	return (huffmanDecompress(argv[2], argv[3]));
}
