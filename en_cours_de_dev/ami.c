#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for buffer size
#define BUFFER_SIZE 256

// Function prototypes
void compress_file(const char *input_file, const char *output_file, const char *method);
void decompress_file(const char *input_file, const char *output_dir, const char *method);

int main()
{
	int choice;
	char input_file[BUFFER_SIZE], output_file[BUFFER_SIZE], output_dir[BUFFER_SIZE], method[BUFFER_SIZE];

	printf("=== File Compression and Decompression ===\n");
	printf("1. Compress File\n");
	printf("2. Decompress File\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	if (choice == 1)
	{
		printf("Enter the input file path: ");
		scanf("%s", input_file);
		printf("Enter the output file path: ");
		scanf("%s", output_file);
		printf("Enter the compression method (zip, 7z, tar): ");
		scanf("%s", method);

		compress_file(input_file, output_file, method);
	}
	else if (choice == 2)
	{
		printf("Enter the input file path: ");
		scanf("%s", input_file);
		printf("Enter the output directory: ");
		scanf("%s", output_dir);
		printf("Enter the decompression method (zip, 7z, tar): ");
		scanf("%s", method);

		decompress_file(input_file, output_dir, method);
	}
	else
	{
		printf("Invalid choice. Exiting.\n");
	}

	return 0;
}

void compress_file(const char *input_file, const char *output_file, const char *method)
{
	char command[BUFFER_SIZE];

	if (strcmp(method, "zip") == 0)
	{
		snprintf(command, BUFFER_SIZE, "zip %s %s", output_file, input_file);
	}
	else if (strcmp(method, "7z") == 0)
	{
		snprintf(command, BUFFER_SIZE, "7z a %s %s", output_file, input_file);
	}
	else if (strcmp(method, "tar") == 0)
	{
		snprintf(command, BUFFER_SIZE, "tar -cf %s %s", output_file, input_file);
	}
	else
	{
		printf("Unsupported compression method: %s\n", method);
		return;
	}

	printf("Executing: %s\n", command);
	int result = system(command);
	if (result == 0)
	{
		printf("File compressed successfully.\n");
	}
	else
	{
		printf("Error compressing file.\n");
	}
}

void decompress_file(const char *input_file, const char *output_dir, const char *method)
{
	char command[BUFFER_SIZE];

	if (strcmp(method, "zip") == 0)
	{
		snprintf(command, BUFFER_SIZE, "unzip %s -d %s", input_file, output_dir);
	}
	else if (strcmp(method, "7z") == 0)
	{
		snprintf(command, BUFFER_SIZE, "7z x %s -o%s", input_file, output_dir);
	}
	else if (strcmp(method, "tar") == 0)
	{
		snprintf(command, BUFFER_SIZE, "tar -xf %s -C %s", input_file, output_dir);
	}
	else
	{
		printf("Unsupported decompression method: %s\n", method);
		return;
	}

	printf("Executing: %s\n", command);
	int result = system(command);
	if (result == 0)
	{
		printf("File decompressed successfully.\n");
	}
	else
	{
		printf("Error decompressing file.\n");
	}
}
