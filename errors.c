#include "shell.h"

/**
 * _eputs - string function
 * @mm: mm string
 * Return: Nothing
 */
void _eputs(char *mm)
{
	int to = 0;

	if (!mm)
		return;
	while (mm[to] != '\0')
	{
		_eputchar(mm[to]);
		to++;
	}
}

/**
 * _eputchar - function print charac
 * @test: test character
 * Return: success 1.
 */
int _eputchar(char test)
{
	static int s;
	static char cmd[WRITE_BUF_SIZE];

	if (test == BUF_FLUSH || s >= WRITE_BUF_SIZE)
	{
		write(2, cmd, s);
		s = 0;
	}
	if (test != BUF_FLUSH)
		cmd[s++] = test;
	return (1);
}

/**
 * _putfd - function int put file descriptor
 * @sb: sb variable
 * @filed: file descriptor
 *
 * Return: successful 1
 */
int _putfd(char sb, int filed)
{
	static int x;
	static char cmd[WRITE_BUF_SIZE];

	if (sb == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(filed, cmd, x);
		x = 0;
	}
	if (sb != BUF_FLUSH)
		cmd[x++] = sb;
	return (1);
}

/**
 * _putsfd - function puts file directory
 * @y: string
 * @im: int
 *
 * Return: number to return
 */
int _putsfd(char *y, int im)
{
	int n = 0;

	if (!y)
		return (0);
	while (*y)
	{
		n += _putfd(*y++, im);
	}
	return (y);
}

