#include "shell.h"

/**
 * is_chain - test if current char
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(infop *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->type_cmd = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->type_cmd = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->type_cmd = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(infop *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->type_cmd == CMD_AND)
	{
		if (info->s)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->type_cmd == CMD_OR)
	{
		if (!info->s)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(infop *info)
{
	int i;
	node_l *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->ai, info->ar[0], '=');
		if (!node)
			return (0);
		free(info->ar[0]);
		p = _strchr(node->s, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->ar[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(infop *info)
{
	int i = 0;
	node_l *node;

	for (i = 0; info->ar[i]; i++)
	{
		if (info->ar[i][0] != '$' || !info->ar[i][1])
			continue;

		if (!_strcmp(info->ar[i], "$?"))
		{
			replace_string(&(info->ar[i]),
					_strdup(convert_number(info->s, 10, 0)));
			continue;
		}
		if (!_strcmp(info->ar[i], "$$"))
		{
			replace_string(&(info->ar[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->vn, &info->ar[i][1], '=');
		if (node)
		{
			replace_string(&(info->ar[i]),
					_strdup(_strchr(node->s, '=') + 1));
			continue;
		}
		replace_string(&info->ar[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

