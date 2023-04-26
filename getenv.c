#include "shell.h"

/**
 * get_environ - function string
 * @i: struct infop
 * Return: Always 0
 */
char **get_environ(infop *i)
{
	if (!i->envi || i->chang_ev)
	{
		i->envi = node_lo_strings(i->vn);
		i->chang_ev = 0;
	}

	return (i->envi);
}

/**
 * _unsetenv - function
 * @i: struct infop
 *  Return: 1 if true
 * @va: string
 */
int _unsetenv(infop *i, char *va)
{
	node_l *node = i->vn;
	size_t ii = 0;
	char *pp;

	if (!node || !va)
		return (0);

	while (node)
	{
		pp = starts_with(node->s, va);
		if (pp && *pp == '=')
		{
			i->chang_ev = delete_node_at_index(&(i->vn), ii);
			i = 0;
			node = i->vn;
			continue;
		}
		node = node->next;
		ii++;
	}
	return (i->chang_ev);
}

/**
 * _setenv - function
 * @i: struct infop
 * @va: string
 * @val: the string
 *  Return: Always 0
 */
int _setenv(infop *i, char *va, char *val)
{
	char *bf = NULL;
	node_l *node;
	char *p;

	if (!va || !val)
		return (0);

	bf = malloc(_strlen(va) + _strlen(val) + 2);
	if (!bf)
		return (1);
	_strcpy(bf, va);
	_strcat(bf, "=");
	_strcat(bf, val);
	node = i->vn;
	while (node)
	{
		p = starts_with(node->s, va);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = bf;
			i->chang_ev = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(i->vn), bf, 0);
	free(bf);
	i->chang_ev = 1;
	return (0);
}

