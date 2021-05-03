# -*- MakeFile -*-
# 0x02. C - Huffman coding - project 286


CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -I../heap/ -I../


# task 10. Huffman - Compression & Decompression

heap_create.o: ../heap/heap.h ../heap/heap_create.c
	$(CC) -c $(CFLAGS) ../heap/heap_create.c

binary_tree_node.o: ../heap/heap.h ../heap/binary_tree_node.c
	$(CC) -c $(CFLAGS) ../heap/binary_tree_node.c

heap_insert.o: ../heap/heap.h ../heap/heap_insert.c
	$(CC) -c $(CFLAGS) ../heap/heap_insert.c

heap_extract.o: ../heap/heap.h ../heap/heap_extract.c
	$(CC) -c $(CFLAGS) ../heap/heap_extract.c

heap_delete.o: ../heap/heap.h ../heap/heap_delete.c
	$(CC) -c $(CFLAGS) ../heap/heap_delete.c

symbol.o: ../huffman.h ../symbol.c
	$(CC) -c $(CFLAGS) ../symbol.c

huffman_priority_queue.o: ../huffman.h ../huffman_priority_queue.c
	$(CC) -c $(CFLAGS) ../huffman_priority_queue.c

huffman_extract_and_insert.o: ../huffman.h ../huffman_extract_and_insert.c
	$(CC) -c $(CFLAGS) ../huffman_extract_and_insert.c

huffman_tree.o: ../huffman.h ../huffman_tree.c
	$(CC) -c $(CFLAGS) ../huffman_tree.c

huffman_codes.o: ../huffman.h ../huffman_codes.c
	$(CC) -c $(CFLAGS) ../huffman_codes.c

#test with other name since huffman is also name of directory
hman: ../heap/heap.h ../huffman.h \
	heap_create.o \
	binary_tree_node.o \
	heap_insert.o \
	heap_extract.o \
	heap_delete.o \
	symbol.o \
	huffman_priority_queue.o \
	huffman_extract_and_insert.o \
	huffman_tree.o \
	huffman_codes.o
	$(CC) $(CFLAGS) ../heap/heap.h ../huffman.h \
	heap_create.o \
	binary_tree_node.o \
	heap_insert.o \
	heap_extract.o \
	heap_delete.o \
	symbol.o \
	huffman_priority_queue.o \
	huffman_extract_and_insert.o \
	huffman_tree.o \
	huffman_codes.o \
	-o hman


.PHONY: clean oclean fclean re

clean:
	$(RM) *~ huffman

oclean:
	$(RM) *.o

fclean: clean oclean

re: oclean huffman
