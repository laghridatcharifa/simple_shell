#include "shell.h"

/**
 * get_history_file - gets
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(infop *info)
{
	char *b, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}

/**
 * write_history - creates
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(infop *info)
{
	ssize_t fd;
	char *fn = get_history_file(info);
	node_l *node = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = info->h; node; node = node->next)
	{
		_putsfd(node->s, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(infop *info)
{
	int i, last1 = 0, lcount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *b = NULL, *fn = get_history_file(info);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	b = malloc(sizeof(char) * (fsize + 1));
	if (!b)
		return (0);
	rdlen = read(fd, b, fsize);
	b[fsize] = 0;
	if (rdlen <= 0)
		return (free(b), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			build_history_list(info, b + last1, lcount++);
			last1 = i + 1;
		}
	if (last1 != i)
		build_history_list(info, b + last1, lcount++);
	free(b);
	info->hc = lcount;
	while (info->hc-- >= HIST_MAX)
		delete_node_at_index(&(info->h), 0);
	renumber_history(info);
	return (info->hc);
}

/**
 * build_history_list - adds entry
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(infop *info, char *buf, int linecount)
{
	node_l *node = NULL;

	if (info->h)
		node = info->h;
	add_node_end(&node, buf, linecount);

	if (!info->h)
		info->h = node;
	return (0);
}

/**
 * renumber_history - renumbers the history
 * @info: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(infop *info)
{
	node_l *node = info->h;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->hc = i);
}

