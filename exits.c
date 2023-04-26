#include "shell.h"

/**
 **_strncpy - function strcpy
 *@d: character d
 *@s: string s
 *@nn: integer variable
 *Return: char return
 */
char *_strncpy(char *d, char *s, int nn)
{
	int a, b;
	char *sv = d;

	a = 0;
	while (s[a] != '\0' && a < nn - 1)
	{
		d[a] = s[a];
		a++;
	}
	if (a < nn)
	{
		b = a;
		while (b < nn)
		{
			d[b] = '\0';
			b++;
		}
	}
	return (sv);
}

/**
 **_strncat - function of strings
 *@d: charcter
 *@s: char
 *@nn: integerd
 *Return: returning char
 */
char *_strncat(char *d, char *s, int nn)
{
	int a, b;
	char *sv = d;

	a = 0;
	b = 0;
	while (d[a] != '\0')
		a++;
	while (s[b] != '\0' && b < nn)
	{
		d[a] = s[b];
		a++;
		b++;
	}
	if (b < nn)
		d[a] = '\0';
	return (sv);
}

/**
 **_strchr - funtion string
 *@q: first characher
 *@z: second character
 *Return: returning char
 */
char *_strchr(char *q, char z)
{
	do {
		if (*q == z)
			return (q);
	} while (*q++ != '\0');

	return (NULL);
}

