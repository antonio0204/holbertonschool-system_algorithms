#include "_huffman.h"
/* binary_tree_node_t */
#include "heap.h"
/* FILE fopen printf */
#include <stdio.h>

void binary_tree_print(const binary_tree_node_t *heap, int (*print_data)(char *, void *));

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



/**
 * huffmanDecompress - TBD
 *
 * @in_file: TBD
 * @out_file: TBD
 * Return: TBD
 */
int huffmanDecompress(FILE *in_file, FILE *out_file)
{
	unsigned char buff[BUF_SIZE] = {0};
	huffman_header_t header;
	binary_tree_node_t *h_tree = NULL;
	bit_t r_bit = {0, 0, 0}/*, w_bit = {0, 0, 0}*/;
	/* temp */
	size_t read_bytes;

	if (!in_file || !out_file)
		return (1);

	/* check header */
	if (fread(&header, sizeof(huffman_header_t), 1, in_file) != 1)
	{
		fclose(in_file);
		fclose(out_file);
		return (1);
	}

	read_bytes = fread(buff, sizeof(unsigned char),
			   BUF_SIZE, in_file);

	printf("\tread_bytes from compressed file:%lu\n", read_bytes);

	h_tree = huffmanDeserialize(buff, &r_bit, NULL);
	if (!h_tree)
		return (1);

	binary_tree_print(h_tree, char_print);

	return (0);
}
