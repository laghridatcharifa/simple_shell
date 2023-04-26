#include "shell.h"

/**
 * is_cmd - determines
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(infop *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char b[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			b[k++] = pathstr[i];
	b[k] = 0;
	return (b);
}

/**
 * find_path - finds this cmd
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(infop *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *pathe;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			pathe = dup_chars(pathstr, curr_pos, i);
			if (!*pathe)
				_strcat(pathe, cmd);
			else
			{
				_strcat(pathe, "/");
				_strcat(pathe, cmd);
			}
			if (is_cmd(info, pathe))
				return (pathe);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

