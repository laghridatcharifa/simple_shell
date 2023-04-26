#include "shell.h"

/**
 * interactive - returns 1 if is interactive mode
 * @i: info struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(infop *i)
{
	return (isatty(STDIN_FILENO) && i->rfd <= 2);
}

/**
 * is_delim - if character is a deli meter
 * @s: the character s to check
 * @de: string
 * Return: 1 if true, 0 if false
 */
int is_delim(char s, char *de)
{
	while (*de)
		if (*de++ == s)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphab character
 * @s: inputing caracter
 * Return: 1 if c is alphab, 0 otherwise
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @c: the character c is string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *c)
{
	int i, s = 1, f = 0, o;
	unsigned int r = 0;

	for (i = 0; c[i] != '\0' && f != 2; i++)
	{
		if (c[i] == '-')
			s *= -1;

		if (c[i] >= '0' && c[i] <= '9')
		{
			f = 1;
			r *= 10;
			r += (c[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (s == -1)
		o = -r;
	else
		o = r;

	return (o);
}

