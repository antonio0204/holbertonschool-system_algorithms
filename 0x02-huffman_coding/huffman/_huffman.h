#ifndef _HUFFMAN_H
#define _HUFFMAN_H

/* binary_tree_node_t */
#include "heap.h"
/* FILE */
#include <stdio.h>

#define BUF_SIZE 1000
#define CHAR_RANGE 256  /* extended ASCII, 128 for normal */

/**
 * struct bit_s - TBD
 *
 * @byte_dix: TBD
 * @byte: TBD
 * @bit_idx: TBD
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

/**
 * struct huffman_header_s - TBD
 *
 * @huff_id: TBD
 * @hc_byte_offset: TBD
 * @hc_first_bit_i: TBD
 * @hc_last_bit_i: TBD
 */
typedef struct huffman_header_s {
	unsigned char huff_id[4];
	unsigned short int hc_byte_offset;
	unsigned char hc_first_bit_i;
	unsigned char hc_last_bit_i;
} huffman_header_t;

/* huffman.c */
FILE *openInputFile(char *input_path);
FILE *openOutputFile(char *output_path);
/* int main(int argc, char *argv[]) */

/* huffmanCompress.c */
size_t *tallyFrequencies(FILE *in_file);
int prepareTreeInputs(size_t *freqs, char **data,
		      size_t **freq, size_t *freq_size);
binary_tree_node_t *HuffmanTreeFromText(FILE *in_file);
int huffmanCompress(FILE *in_file, FILE *out_file);

/* huffmanDecompress.c */
int huffmanDecompress(FILE *in_file, FILE *out_file);

/* serialization.c */
void huffmanSerialize(binary_tree_node_t *huffman_tree,
		      unsigned char *buff, bit_t *w_bit);
binary_tree_node_t *huffmanDeserialize(unsigned char *buff, bit_t *r_bit,
				       binary_tree_node_t *parent);

/* read_write.c */
int readBit(unsigned char *buff, bit_t *r_bit, unsigned char *value);
int readByte(unsigned char *buff, bit_t *r_bit, unsigned char *byte);
int writeBit(unsigned char *buff, bit_t *w_bit, unsigned char toggle);
int writeByte(unsigned char *buff, bit_t *w_bit, unsigned char byte);
int writePartialByte(unsigned char *buff, bit_t *w_bit);


#endif /* _HUFFMAN_H */
