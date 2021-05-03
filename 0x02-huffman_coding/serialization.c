#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "huffman.h"


void huffmanSerializationTest(binary_tree_node_t *huffman_tree, char *buff, size_t *i)
{
/*
	printf(" %lu:", ((symbol_t *)(huffman_tree->data))->freq);
*/
	if (!huffman_tree || !buff)
		return;

	if (!huffman_tree->left && !huffman_tree->right)
	{
		buff[*i] = '1';
		(*i)++;
		buff[*i] = ((symbol_t *)(huffman_tree->data))->data;
		(*i)++;
		return;
	}

	buff[*i] = '0';
	(*i)++;
	huffmanSerializationTest(huffman_tree->left, buff, i);
	huffmanSerializationTest(huffman_tree->right, buff, i);
}


binary_tree_node_t *huffmanDeserializationTest(char *buff, size_t *i, binary_tree_node_t *parent)
{
	binary_tree_node_t *new = NULL;

	if (!buff || !i)
		return (NULL);

	if (buff[*i] == '1')
	{
		(*i)++;
		new = binary_tree_node(parent, buff + *i);
		(*i)++;
		return (new);
	}

	(*i)++;
	new = binary_tree_node(parent, NULL);
	new->left = huffmanDeserializationTest(buff, i, new);
	new->right = huffmanDeserializationTest(buff, i, new);

	return (new);
}

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
    length = sprintf(buffer, "(%c)", c);
    return (length);
}


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
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	binary_tree_node_t *root = NULL, *deserial = NULL;
    char *serial = NULL;
    char data[] = {
        'a', 'b', 'c', 'd', 'e', 'f'
    };
    size_t freq[] = {
        6, 11, 12, 13, 16, 36
    };
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t i;

    /* need to find a way to calculate buffsize */
    serial = calloc(200, sizeof(char));
    if (!serial)
	    return (EXIT_FAILURE);

    root = huffman_tree(data, freq, size);
    if (!root)
    {
        fprintf(stderr, "Failed to build Huffman tree\n");
        return (EXIT_FAILURE);
    }
    binary_tree_print(root, symbol_print);

    i = 0;
    huffmanSerializationTest(root, serial, &i);
    printf("serialized: %s\n", serial);

    i = 0;
    deserial = huffmanDeserializationTest(serial, &i, NULL);
    binary_tree_print(deserial, char_print);

    binaryTreeDelete(root, freeSymbol);
    free(serial);
    binaryTreeDelete(deserial, NULL);

    return (EXIT_SUCCESS);
}
