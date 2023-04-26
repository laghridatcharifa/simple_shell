#include "shell.h"

/**
 * **strtow - splits a string into words
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, nw = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	st = malloc((1 + nw) * sizeof(char *));
	if (!st)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[i++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

/**
 * **strtow2 - splits a string
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, nw = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			nw++;
	if (nw == 0)
		return (NULL);
	st = malloc((1 + nw) * sizeof(char *));
	if (!st)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[i++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

