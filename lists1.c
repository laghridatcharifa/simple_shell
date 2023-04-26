#include "shell.h"

/**
 * list_len - determines length
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const node_l *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_lo_strings - returns an array
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **node_lo_strings(node_l *head)
{
	node_l *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *s;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_strlen(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		s = _strcpy(s, node->s);
		strs[i] = s;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const node_l *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
node_l *node_starts_with(node_l *node, char *prefix, char c)
{
	char *pl = NULL;

	while (node)
	{
		pl = starts_with(node->s, prefix);
		if (pl && ((c == -1) || (*pl == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(node_l *head, node_l *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

