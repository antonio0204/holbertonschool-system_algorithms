#include "_huffman.h"
/* binary_tree_node_t */
#include "heap.h"
/* malloc */
#include <stdlib.h>
/* fread feof fclose */
#include <stdio.h>
/* memset */
#include <string.h>

/* symbol_t */
#include "huffman.h"

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
 * tallyFrequencies - TBD
 *
 * @in_file: TBD
 * Return: TBD
 */
size_t *tallyFrequencies(FILE *in_file)
{
	size_t *freqs = NULL;
	size_t i, read_bytes;
	unsigned char buff[BUF_SIZE] = {0};

	if (!in_file)
		return (NULL);

	freqs = malloc(sizeof(size_t) * CHAR_RANGE);
	if (!freqs)
		return (NULL);
	memset(freqs, 0, sizeof(size_t) * CHAR_RANGE);

        do {
		read_bytes = fread(buff, sizeof(unsigned char),
				   BUF_SIZE, in_file);

		printf("\ttallyFrequencies: read_bytes from text input:%lu\n", read_bytes);

		for (i = 0; i < read_bytes; i++)
			freqs[buff[i]]++;
	} while (read_bytes == BUF_SIZE);

	if (!feof(in_file))
	{
		free(freqs);
		return (NULL);
	}

	rewind(in_file);

	for (i = 0; i < read_bytes; i++)
		freqs[buff[i]]++;

	return (freqs);
}


/* build inputs to match existing huffman_tree() prototype */
/**
 * prepareTreeInputs - TBD
 *
 * @freqs: TBD
 * @data: TBD
 * @freq: TBD
 * @freq_size: TBD
 * Return: TBD
 */
int prepareTreeInputs(size_t *freqs, char **data,
		      size_t **freq, size_t *freq_size)
{
	size_t i, j;

	if (!freqs || !data || !freq || !freq_size)
		return (1);

	for (i = 0, *freq_size = 0; i < CHAR_RANGE; i++)
		if (freqs[i])
			(*freq_size)++;

	*data = malloc(sizeof(char) * *freq_size);
	if (!(*data))
		return (1);

	*freq = malloc(sizeof(size_t) * *freq_size);
	if (!(*freq))
	{
		free((*data));
		return (1);
	}

	for (i = 0, j = 0; i < CHAR_RANGE && j < *freq_size; i++)
	{
		if (freqs[i])
		{
			(*freq)[j] = freqs[i];
			(*data)[j] = (char)i;
			j++;
		}
	}

	return (0);
}


/**
 * prepareTreeInputs - TBD
 *
 * @freqs: TBD
 * @data: TBD
 * @freq: TBD
 * @freq_size: TBD
 * Return: TBD
 */
binary_tree_node_t *huffmanTreeFromText(FILE *in_file, size_t *freq_size)
{
	size_t *freqs = NULL, *freq = NULL;
	size_t i;
	char *data = NULL;
	binary_tree_node_t *h_tree = NULL;

	if (!in_file)
		return (NULL);

	freqs = tallyFrequencies(in_file);
	if (!freqs)
		return (NULL);

	if (prepareTreeInputs(freqs, &data, &freq, freq_size) == 1)
	{
		free(freqs);
		return (NULL);
	}
	free(freqs);

	for (i = 0; i < *freq_size; i++)
	{
		if (data[i] < ' ' || data[i] > '~')
			printf("\ti:%lu data:%x freq:%lu", i, data[i], freq[i]);
		else
			printf("\ti:%lu data:'%c' freq:%lu", i, data[i], freq[i]);
		if (i % 2)
			putchar('\n');
	}

	h_tree = huffman_tree(data, freq, *freq_size);
	free(data);
	free(freq);
	return (h_tree);
}


/**
 * huffmanCompress - TBD
 *
 * @in_file: TBD
 * @out_file: TBD
 * Return: TBD
 */
int huffmanCompress(FILE *in_file, FILE *out_file)
{
	unsigned char w_buff[BUF_SIZE] = {0};
	huffman_header_t header = {"\177HUF", 0, 0, 0};
	binary_tree_node_t *h_tree = NULL;
	bit_t w_bit = {0, 0, 0};
	size_t freq_size = 0;

	if (!in_file || !out_file)
		return (1);

	h_tree = huffmanTreeFromText(in_file, &freq_size);
	if (!h_tree)
		return (1);

	binary_tree_print(h_tree, symbol_print);

	huffmanSerialize(h_tree, w_buff, &w_bit);
	/* if partial byte reamins, write to last byte in buffer */
	if (writePartialByte(w_buff, &w_bit) == 1)
	{
		fclose(in_file);
		fclose(out_file);
		binaryTreeDelete(h_tree, freeSymbol);
		return (1);
	}

	/* huffman code starts at bit after serialized tree */
	header.hc_byte_offset = sizeof(huffman_header_t) + w_bit.byte_idx;
        header.hc_first_bit_i = w_bit.bit_idx;

	if (huffmanEncode(in_file, h_tree, freq_size, w_buff, &w_bit) == 1 ||
	    writePartialByte(w_buff, &w_bit) == 1)
	{
		fclose(in_file);
		fclose(out_file);
		binaryTreeDelete(h_tree, freeSymbol);
		return (1);
	}

        header.hc_last_bit_i = w_bit.bit_idx;

	fclose(in_file);
	binaryTreeDelete(h_tree, freeSymbol);

	/* write header to file */
        if (fwrite(&header, sizeof(huffman_header_t), 1, out_file) != 1)
	{
		fclose(out_file);
		return (1);
	}

	/* write serialized tree and encoded teto file */
        if (fwrite(w_buff, sizeof(unsigned char), w_bit.byte_idx + 1,
		   out_file) != w_bit.byte_idx + 1)
	{
		fclose(out_file);
		return (1);
	}

	fclose(out_file);
	return (0);
}
