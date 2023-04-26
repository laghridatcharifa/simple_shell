#include "shell.h"

/**
 * clear_info - function
 * @info: struct infop
 */
void clear_info(infop *info)
{
	info->a = NULL;
	info->ar = NULL;
	info->p = NULL;
	info->ac = 0;
}

/**
 * set_info - function
 * @info: struct infop
 * @a: vector
 */
void set_info(infop *info, char **a)
{
	int i = 0;

	info->fn = a[0];
	if (info->a)
	{
		info->ar = strtow(info->a, " \t");
		if (!info->ar)
		{
			info->ar = malloc(sizeof(char *) * 2);
			if (info->ar)
			{
				info->ar[0] = _strdup(info->a);
				info->ar[1] = NULL;
			}
		}
		for (i = 0; info->ar && info->ar[i]; i++)
			;
		info->ac = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - function
 * @info: struct infop
 * @al: int
 */
void free_info(infop *info, int al)
{
	ffree(info->ar);
	info->ar = NULL;
	info->p = NULL;
	if (al)
	{
		if (!info->buf_cmd)
			free(info->a);
		if (info->vn)
			free_list(&(info->vn));
		if (info->h)
			free_list(&(info->h));
		if (info->ai)
			free_list(&(info->ai));
		ffree(info->envi);
			info->envi = NULL;
		bfree((void **)info->buf_cmd);
		if (info->rfd > 2)
			close(info->rfd);
		_putchar(BUF_FLUSH);
	}
}

