#include "_huffman.h"
/* printf */
#include <stdio.h>
/* stat */
#include <sys/types.h>
#include <sys/stat.h>
/* access stat */
#include <unistd.h>
/* strlen */
#include <string.h>
#include <errno.h>


/**
 * openInputFile - TBD
 *
 * @input_path: TBD
 * Return: TBD
 */
FILE *openInputFile(char *input_path, struct stat *st)
{
	FILE *in_file = NULL;

	if (!input_path || !st)
		return (NULL);

	if (access(input_path, F_OK | R_OK) == -1)
	{
		switch (errno)
		{
		case ENOENT:
			printf("No such file: %s\n", input_path);
			break;
		case EACCES:
			printf("No read permission for file: %s\n",
			       input_path);
			break;
		default:
		        printf("Cannot access file: %s", input_path);
			break;
		}
		return (NULL);
	}

	if (stat(input_path, st) != -1 && !S_ISREG(st->st_mode))
	{
		printf("Not regular file: %s\n", input_path);
		return (NULL);
	}

	in_file = fopen(input_path, "r");
	if (!in_file)
	{
		perror("openInputfile: fopen");
		errno == 0;
	}

	return (in_file);
}


/**
 * openOutputFile - TBD
 *
 * @output_path: TBD
 * Return: TBD
 */
FILE *openOutputFile(char *output_path)
{
	FILE *out_file = NULL;

	out_file = fopen(output_path, "w");
	if (!out_file)
		perror("openOutputfile: fopen");

	return (out_file);
}


/* no need for envp? locale should have no impact on sorting ASCII */
/* do we need to handle Unicode? */
/**
 * main - entry point to `huffman`
 *
 * @argc: TBD
 * @argv: TBD
 * Return: TBD
 */
int main(int argc, char *argv[])
{
	FILE *in_file = NULL, *out_file = NULL;
	int ret_val;
	struct stat st;

	if (argc != 4 ||
	    strlen(argv[1]) != 1 ||
	    (argv[1][0] != 'c' && argv[1][0] != 'd'))
	{
		printf("Usage: huffman <mode> <filename> <out_filename>\n");
		return (1);
	}

	in_file = openInputFile(argv[2], &st);
	if (!in_file)
		return (1);

	out_file = openOutputFile(argv[3]);
	if (!out_file)
	{
		fclose(in_file);
		return (1);
	}

	if (argv[1][0] == 'c')
		return (huffmanCompress(in_file, out_file));

	/* off_t is defined as long int in sys/types.h */
        ret_val = huffmanDecompress(in_file, out_file, (long int)st.st_size);
	fclose(in_file);
	fclose(out_file);
	return (ret_val);
}
