#include "_huffman.h"
/* binary_tree_node_t */
#include "heap.h"
/* readBit */
#include "huffman.h"
/* fwrite */
#include <stdio.h>
/* memset */
#include <string.h>


/**
 * decodeSingleChar - TBD
 *
 * @h_tree: TBD
 * @r_buff: TBD
 * @w_bit: TBD
 * Return: TBD
 */
char *decodeSingleChar(binary_tree_node_t *h_tree,
		       unsigned char *r_buff, bit_t *r_bit)
{
	unsigned char bit;

	if (!h_tree || !r_buff || !r_bit)
		return (NULL);

	if (!h_tree->left && !h_tree->right)
		return ((char *)(h_tree->data));

	if (readBit(r_buff, r_bit, &bit) == 1)
		return (NULL);

	if (bit == 0)
		return (decodeSingleChar(h_tree->left, r_buff, r_bit));

	return (decodeSingleChar(h_tree->right, r_buff, r_bit));
}


/**
 * huffmanDecode - TBD
 *
 * @out_file: TBD
 * @h_tree: TBD
 * @header: TBD
 * @input_file_size: TBD
 * @r_buff: TBD
 * @r_bit: TBD
 * Return: TBD
 */
int huffmanDecode(FILE *out_file, binary_tree_node_t *h_tree,
		  huffman_header_t *header, long int input_file_size,
		  unsigned char *r_buff, bit_t *r_bit)
{
	unsigned char w_buff[BUF_SIZE] = {0};
	char *c = NULL;
	size_t i = 0, size_minus_header, read_bytes;

	if (!out_file || !h_tree || !header || !r_buff || !r_bit)
		return (1);

	size_minus_header = (size_t)input_file_size - sizeof(*header);

	printf("huffmanDecode: size_minus_header:%lu header->hc_last_bit_i:%u header->hc_byte_offset:%u header->hc_first_bit_i:%u\n",
	       size_minus_header, header->hc_last_bit_i, header->hc_byte_offset, header->hc_first_bit_i);

	printf("huffmanDecode: r_bit->byte_idx:%lu r_bit->bit_idx:%u\n",
	       r_bit->byte_idx, r_bit->bit_idx);

	while (r_bit->byte_idx < size_minus_header - 1 ||
	       (r_bit->byte_idx == size_minus_header - 1 &&
		r_bit->bit_idx < header->hc_last_bit_i))
	{
		c = decodeSingleChar(h_tree, r_buff, r_bit);
		if (c == NULL)
			return (1);

		w_buff[i] = *c;
		i++;

		if (i == BUF_SIZE)
		{
			printf("huffmanDecode: writing and refreshing buffer\n");

			if (fwrite(w_buff, sizeof(unsigned char),
				   1, out_file) != BUF_SIZE)
				return (1);

			i = 0;
			memset(w_buff, 0, BUF_SIZE);
		}
	}
	printf("huffmanDecode: i after decode loop: %lu\n", i);


	/* file bytes % BUF_SIZE */
	if (i != BUF_SIZE)
	{
	        read_bytes = fwrite(w_buff, sizeof(unsigned char),
				    i, out_file);
		printf("huffmanDecode: last read read_bytes: %lu\n", read_bytes);

		if (read_bytes != i)
			return (1);
	}

	return (0);
}
