#include "shell.h"

/**
 * _erratoi - functionconvertion to int
 * @ha: string
 * Return: 0 when no convert
 */
int _erratoi(char *ha)
{
	int ii = 0;
	unsigned long int re = 0;

	if (*ha == '+')
		ha++;  /* TODO: why does this make main return 255? */
	for (ii = 0;  ha[ii] != '\0'; ii++)
	{
		if (ha[ii] >= '0' && ha[ii] <= '9')
		{
			re *= 10;
			re += (ha[ii] - '0');
			if (re > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (re);
}

/**
 * print_error - function void to write an error
 * @i: struct infop
 * @et: character
 * Return: 0 in case no character
 */
void print_error(infop *i, char *et)
{
	_eputs(i->fn);
	_eputs(": ");
	print_d(i->lc, STDERR_FILENO);
	_eputs(": ");
	_eputs(i->ar[0]);
	_eputs(": ");
	_eputs(et);
}

/**
 * print_d - printing a number in base 10
 * @pt: variable
 * @yn: file descriptor
 * Return: return the number of character
 */
int print_d(int pt, int yn)
{
	int (*__putchar)(char) = _putchar;
	int x, c = 0;
	unsigned int test, cr;

	if (yn == STDERR_FILENO)
		__putchar = _eputchar;
	if (pt < 0)
	{
		test = -pt;
		__putchar('-');
		c++;
	}
	else
		test = pt;
	cr = test;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (test / x)
		{
			__putchar('0' + cr / x);
			c++;
		}
		cr %= x;
	}
	__putchar('0' + cr);
	c++;

	return (c);
}

/**
 * convert_number - function to convert
 * @n: int
 * @e: int
 * @s: integer
 *
 * Return: string
 */
char *convert_number(long int n, int e, int s)
{
	static char *ar;
	static char bu[50];
	char g = 0;
	char *tr;
	unsigned long i = n;

	if (!(s & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		g = '-';

	}
	ar = s & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	tr = &bu[49];
	*tr = '\0';

	do	{
		*--tr = ar[n % e];
		i /= e;
	} while (i != 0);

	if (g)
		*--tr = g;
	return (tr);
}

/**
 * remove_comments - passsing men \0 to #
 * @b: char
 * Return: Always 0;
 */
void remove_comments(char *b)
{
	int ii;

	for (ii = 0; b[ii] != '\0'; ii++)
		if (b[ii] == '#' && (!ii || b[ii - 1] == ' '))
		{
			b[ii] = '\0';
			break;
		}
}

