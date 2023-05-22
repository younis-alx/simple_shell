#include "main.h"
#include <errno.h>
/**
 * _strdup - strdup implementation
 * @str: str to duplicate
 *
 * Return: copy a str
 */
char *_strdup(const char *str)
{
	int i, n = 0;
	char *strcopy;

	if (str == NULL)
		return (NULL);
	do {
		n++;
	} while (str[n - 1]);
	strcopy = malloc(sizeof(char) * n);
	if (strcopy == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
	{
		strcopy[i] = str[i];
	}
	return (strcopy);
}


/**
 * _getline - reads input and store it to address [getline] implementation
 * @lineptr: pointer to line
 * @n: size to read
 * @stream: stream
 * Return: pos
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    char *new_ptr;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

/**
 * path - if a file exists
 * @filename: name of the file
 *
 * Return:  absolute path of file or NULL
 */
char *path(char *filename)
{
	char *PATH = _getenv("PATH");
	char *clone = _strdup(PATH), *concat = NULL;
	char *token = NULL, *absolute = NULL;
	struct stat st;

	token = _strtok(clone, ':');
	concat = str_concat("/", filename);
	while (token != NULL)
	{
		absolute = str_concat(token, concat);
		if (stat(absolute, &st) == 0)
		{
			free(PATH);
			free(clone);
			free(concat);
			return (absolute);
		}
		token = _strtok(NULL, ':');
		free(absolute);
	}
	free(PATH);
	free(concat);
	free(clone);
	return (NULL);
}