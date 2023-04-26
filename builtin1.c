#include "shell.h"

/**
 * _myhistory - history list displ
 * @i: Structure of infop
 *  Return: Always 0
 */
int _myhistory(infop *i)
{
	print_list(i->h);
	return (0);
}

/**
 * unset_alias - sets function
 * @i: infop struct
 * @c: the character of alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(infop *i, char *c)
{
	char *n, m;
	int t;

	n = _strchr(c, '=');
	if (!n)
		return (1);
	c = *n;
	*n = 0;
	t = delete_node_at_index(&(i->ai),
		get_node_index(i->ai, node_starts_with(i->ai, c, -1)));
	*n = m;
	return (t);
}

/**
 * set_alias - sets alias to string
 * @i: struct infop
 * @s: the character of alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(infop *i, char *s)
{
	char *inf;

	inf = _strchr(s, '=');
	if (!inf)
		return (1);
	if (!*++s)
		return (unset_alias(i, s));

	unset_alias(i, s);
	return (add_node_end(&(i->ai), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @list: the node list
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(node_l *list)
{
	char *l = NULL, *j = NULL;

	if (list)
	{
		l = _strchr(list->s, '=');
		for (j = list->s; j <= l; j++)
		_putchar(*j);
		_putchar('\'');
		_puts(l + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - man alias
 * @i: Struct info
 *  Return: Always 0
 */
int _myalias(infop *i)
{
	int ii = 0;
	char *c = NULL;
	node_l *n = NULL;

	if (i->ar == 1)
	{
		n = i->ai;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (ii = 1; i-> ar[ii]; ii++)
	{
		c = _strchr(i->ar[ii], '=');
		if (c)
			set_alias(i, i->ar[ii]);
		else
			print_alias(node_starts_with(i->ai, i->ar[ii], '='));
	}

	return (0);
}

