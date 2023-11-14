#include "shell.h"
#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_index;
static size_t buffer_size;
/**
 * custom_getline - Reads a line from standard input.
 * Returns a dynamically allocated string containing the line.
 * Returns NULL on error or end of input.
 */
char *custom_getline(void)
{
	char *line = NULL;
	size_t line_size = 0;
	char current_char;

	while (1)
	{
		/* If buffer is empty, read more characters */
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			/* Check for end of input or error */
			if (buffer_size <= 0)
			{
				/* If no characters read, return NULL (end of input or error) */
				if (line_size == 0)
				{
					return (NULL);
				}
				break; /* Otherwise, break and return the current line */
			}
			buffer_index = 0; /* Reset buffer index */
		}
		/* Read characters from buffer */
		current_char = buffer[buffer_index++];
		/* If a newline character is encountered, terminate the line and return */
		if (current_char == '\n')
		{
			break;
		}
		/* Allocate memory for the line and add the current character */
		line = realloc(line, line_size + 1);
		if (line == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		line[line_size++] = current_char;
	}
    /* Add null terminator to the line*/
	line = realloc(line, line_size + 1);
	if (line == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	line[line_size] = '\0';
	return (line);
}
