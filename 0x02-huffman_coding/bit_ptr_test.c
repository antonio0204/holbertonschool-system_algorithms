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


int readBit(unsigned char *buff, bit_t *r_bit, unsigned char *value)
{
	if (!buff || !r_bit || !value)
		return (1);

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

	for (i = 0; i < 8; i++)
	{
		if (readBit(buff, r_bit, &bit_value) == 1)
			return (1);

		if (bit_value)
			*byte |= (1 << (7 - i));
		else
		        *byte &= ~(1 << (7 - i));
	}

	return (0);
}


int writeBit(unsigned char *buff, bit_t *w_bit, unsigned char toggle)
{
	int i;

	if (!buff || !w_bit || (toggle != 0 && toggle != 1))
		return (1);

	printf("\twriting toggle:%c to buff byte:%lu bit:%u\n", toggle + '0', w_bit->byte_idx, w_bit->bit_idx);

	if (toggle)
		w_bit->byte |= (1 << (7 - w_bit->bit_idx));
	else
		w_bit->byte &= ~(1 << (7 - w_bit->bit_idx));
	w_bit->bit_idx++;

	if (w_bit->bit_idx == 8)
	{
		printf("\t\twriting byte: ");
		for (i = 0; i < 8; i++)
		{
			if (w_bit->byte & 1 << i)
				putchar('1');
			else
				putchar('0');
		}
		printf(" to buff index:%lu\n", w_bit->byte_idx);

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

	printf("\twriting char:%c\n", (char)byte);

	if (!buff || !w_bit)
		return (1);

	for (i = 0; i < 8; i++)
	{
/*
		printf("\tbyte & (1 << %lu) -> byte & %#x -> %i\n", i, 1 << i, byte & (1 << i));
*/
		if (writeBit(buff, w_bit, (byte & (1 << (7 - i))) ? 1 : 0) == 1)
			return (1);
	}
	printf("\tend writing char:%c\n", (char)byte);

	return (0);
}


/* write: "01f001c1d01e01a1b" */
int huffmanCompress(char *in_file, char *out_file)
{
	unsigned char buff[50] = {0};
	FILE /**infile = NULL, */*outfile = NULL;
	bit_t w_bit = {0, 0, 0};

	(void)in_file;
        outfile = fopen(out_file, "w");
	if (!outfile)
		return (1);

	printf("write to file: \"01f001c1d01e01a1b\"\n");

	writeBit(buff, &w_bit, 0);
	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'f');

	writeBit(buff, &w_bit, 0);
	writeBit(buff, &w_bit, 0);
	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'c');

	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'd');

	writeBit(buff, &w_bit, 0);
	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'e');

	writeBit(buff, &w_bit, 0);
	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'a');

	writeBit(buff, &w_bit, 1);
	writeByte(buff, &w_bit, 'b');

	if (w_bit.bit_idx != 0)
	{
		/* write partial byte to last byte in buffer */
		w_bit.bit_idx = 0;
		writeByte(buff, &w_bit, w_bit.byte);
		w_bit.byte_idx -= 1;
	}

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
/*
	printf("%s\n", buff);
*/
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
