#include "shell.h"

/**
 * _myenv - function of current environment
 * @i: Structure of infop
 * Return: Always 0
 */
int _myenv(infop *i)
{
	print_list_str(i->vn);
	return (0);
}

/**
 * _getenv - function to gets environ variable
 * @i: Structure of infop
 * @v:character v
 *
 * Return: the value
 */
char *_getenv(infop *i, const char *v)
{
	node_l *list = i->vn;
	char *t;

	while (list)
	{
		t = starts_with(list->s, v);
		if (t && *t)
			return (t);
		list = list->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function to define new environment variable
 * @i: Structure infop
 *  Return: Always 0
 */
int _mysetenv(infop *i)
{
	if (i->ac != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(i, i->ar[1], i->ar[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function to delete environment variable
 * @i: Structure infop
 * Return: Always 0
 */
int _myunsetenv(infop *i)
{
	int a;

	if (i->ar == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= i->ac; a++)
		_unsetenv(i, i->ar[a]);

	return (0);
}

/**
 * populate_env_list - a function populate_env_list
 * @i: Structure infop
 * Return: Always 0
 */
int populate_env_list(infop *i)
{
	node_l *list = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&list, environ[j], 0);
	i->vn = list;
	return (0);
}

