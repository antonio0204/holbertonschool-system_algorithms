/* includes heap.h */
#include "huffman.h"
/* malloc calloc free */
#include <stdlib.h>
/* printf */
#include <stdio.h>


/**
 * printAllHuffmanCodes - TBD
 *
 * @tree: TBD
 * @depth: TBD
 * @data: TBD
 * @freq: TBD
 * @data_sz: TBD
 * @h_code: TBD
 */
void printAllHuffmanCodes(binary_tree_node_t *tree, size_t depth,
			  char *data, size_t *freq, size_t data_sz,
			  char *h_code)
{
	symbol_t *symbol = NULL;
	size_t i;

	if (!tree || !h_code)
		return;

	if (depth)
		h_code[depth - 1] = (tree == tree->parent->left) ? '0' : '1';

	symbol = (symbol_t *)(tree->data);
	for (i = 0; i < data_sz; i++)
	{
		if (symbol->data == data[i] && symbol->freq == freq[i])
		{
			printf("%c: %s\n", data[i], h_code);
			return;
		}
	}

	printAllHuffmanCodes(tree->left, depth + 1,
			     data, freq, data_sz, h_code);
	printAllHuffmanCodes(tree->right, depth + 1,
			     data, freq, data_sz, h_code);
}


/**
 * deriveHuffmanCode - TBD
 *
 * @tree: TBD
 * @data: TBD
 * @freq: TBD
 * @depth: TBD
 * Return: TBD
 */
char *deriveHuffmanCode(binary_tree_node_t *tree,
			char data, size_t freq, size_t depth)
{
	symbol_t *symbol = NULL;
	char *h_code = NULL, *L_return = NULL, *R_return = NULL;

	if (!tree)
		return (NULL);

	symbol = (symbol_t *)(tree->data);
	if (symbol->data == data && symbol->freq == freq)
	{
		h_code = malloc(sizeof(char) * (depth + 1));
		if (!h_code)
			return (NULL);
		h_code[depth] = '\0';
		if (depth)
			h_code[depth - 1] =
				(tree == tree->parent->left) ? '0' : '1';
		return (h_code);
	}

	L_return = deriveHuffmanCode(tree->left, data, freq, depth + 1);
	if (L_return)
	{
		if (depth)
			L_return[depth - 1] =
				(tree == tree->parent->left) ? '0' : '1';
		return (L_return);
	}

	R_return = deriveHuffmanCode(tree->right, data, freq, depth + 1);
	if (R_return)
	{
		if (depth)
			R_return[depth - 1] =
				(tree == tree->parent->left) ? '0' : '1';
		return (R_return);
	}

	return (NULL);
}


/**
 * huffman_codes - TBD
 *
 * @data: TBD
 * @freq: TBD
 * @size: TBD
 * Return: TBD
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *h_tree = NULL;
	char *h_code = NULL;

	if (!data || !freq || size == 0)
		return (0);

	h_tree = huffman_tree(data, freq, size);
	if (!h_tree)
		return (0);

	h_code = calloc(size, sizeof(char));
	if (!h_code)
		return (0);

	printAllHuffmanCodes(h_tree, 0, data, freq, size, h_code);
	free(h_code);

	binaryTreeDelete(h_tree, freeSymbol);

	return (1);
}
