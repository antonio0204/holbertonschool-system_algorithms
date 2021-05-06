#include "_huffman.h"
/* binary_tree_node_t */
#include "heap.h"
/* FILE fopen printf */
#include <stdio.h>
/* free */
#include <stdlib.h>
/* strncmp */
#include <string.h>


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

    if (data == NULL)
	    length = sprintf(buffer, "($)");
    else
    {
	    c = *((char *)data);

	    if (c < ' ' || c > '~')
		    length = sprintf(buffer, "(%o)", c);
	    else
		    length = sprintf(buffer, "('%c')", c);
    }

    return (length);
}


/**
 * freeChar - meant to be used as free_data parameter to heap_delete or
 *   binaryTreeDelete; frees memory allocated for a char
 *
 * @data: void pointer intended to be cast into data pointer
 */
void freeChar(void *data)
{
        if (data)
                free((char *)data);
}


/**
 * huffmanDecompress - TBD
 *
 * @in_file: TBD
 * @out_file: TBD
 * Return: TBD
 */
int huffmanDecompress(FILE *in_file, FILE *out_file, long int input_file_size)
{
	unsigned char r_buff[BUF_SIZE] = {0};
	bit_t r_bit = {0, 0, 0};
	huffman_header_t header;
	binary_tree_node_t *h_tree = NULL;
	size_t read_bytes;

	if (!in_file || !out_file || input_file_size < 0)
		return (1);

	if (fread(&header, sizeof(huffman_header_t), 1, in_file) != 1)
		return (1);

	if (strncmp((char *)(header.huff_id), "\177HUF", 4) != 0)
	{
		printf("Input is not a file compressed by this program!\n");
		return (1);
	}

	/* one buffer should suffice - serialized trees <= 512 bytes */
	read_bytes = fread(r_buff, sizeof(unsigned char),
			   BUF_SIZE, in_file);
	printf("\tread_bytes from compressed file:%lu\n", read_bytes);

	h_tree = huffmanDeserialize(r_buff, &r_bit, NULL);
	if (!h_tree)
		return (1);

	binary_tree_print(h_tree, char_print);

	if (huffmanDecode(out_file, h_tree, &header, input_file_size,
			  r_buff, &r_bit) == 1)
	{
		binaryTreeDelete(h_tree, freeChar);
		return (1);
	}
	binaryTreeDelete(h_tree, freeChar);

	return (0);
}
