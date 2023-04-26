#include "shell.h"

/**
 * find_builtin - finds a builtin
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(infop *info)
{
	int i, built = -1;
	tableb builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].t; i++)
		if (_strcmp(info->ar[0], builtintbl[i].t) == 0)
		{
			info->lc++;
			built = builtintbl[i].fu(info);
			break;
		}
	return (built);
}

/**
 * hsh - main shell
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(infop *info, char **av)
{
	ssize_t r = 0;
	int builtin = 0;

	while (r != -1 && builtin != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin = find_builtin(info);
			if (builtin == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->s)
		exit(info->s);
	if (builtin == -2)
	{
		if (info->en == -1)
			exit(info->s);
		exit(info->en);
	}
	return (builtin);
}

/**
 * find_cmd - finds a command
 * @info: the parameter & return info struct
 * Return: void
 */
void find_cmd(infop *info)
{
	char *path = NULL;
	int i, k;

	info->p = info->ar[0];
	if (info->lf == 1)
	{
		info->lc++;
		info->lf = 0;
	}
	for (i = 0, k = 0; info->a[i]; i++)
		if (!is_delim(info->a[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->ar[0]);
	if (path)
	{
		info->p = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->ar[0][0] == '/') && is_cmd(info, info->ar[0]))
			fork_cmd(info);
		else if (*(info->a) != '\n')
		{
			info->s = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(infop *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->p, info->ar, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->s));
		if (WIFEXITED(info->s))
		{
			info->s = WEXITSTATUS(info->s);
			if (info->s == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

