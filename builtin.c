#include "shell.h"

/**
 * _myexit - exits the shell
 * @i: Struct info
 * Return: given exit status
 */
int _myexit(infop  *i)
{
	int c;

	if (i->ar[1]) /* If there is an exit arguement */
	{
		c = _erratoi(i->ar[1]);
		if (c == -1)
		{
			i->s = 2;
			print_error(i, "Illegal : ");
			_eputs(i->ar[1]);
			_eputchar('\n');
			return (1);
		}
		i->en = _erratoi(i->ar[1]);
		return (-2);
	}
	i->en = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @i: Struct info
 * Return: Always 0
 */
int _mycd(infop  *i)
{
	char *ss, *d, b[1024];
	int ct;

	ss = getcwd(b, 1024);
	if (!ss)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!i->ar[1])
	{
		d = _getenv(i, "HOME=");
		if (!d)
			ct = /* TODO: what should this be? */
				chdir((d = _getenv(i, "PWD=")) ? d : "/");
		else
			ct = chdir(d);
	}
	else if (_strcmp(i->ar[1], "-") == 0)
	{
		if (!_getenv(i, "OLDPWD="))
		{
			_puts(ss);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(i, "OLDPWD=")), _putchar('\n');
		ct = /* TODO: what should this be? */
			chdir((d = _getenv(i, "OLDPWD=")) ? d : "/");
	}
	else
		ct = chdir(i->ar[1]);
	if (ct == -1)
	{
		print_error(i, "can't cd to ");
		_eputs(i->ar[1]), _eputchar('\n');
	}
	else
	{
		_setenv(i, "OLDPWD", _getenv(i, "PWD="));
		_setenv(i, "PWD", getcwd(b, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the directory of the process
 * @i: Struct infop
 * Return: Always 0
 */
int _myhelp(infop  *i)
{
	char **arr;

	arr = i->ar;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arr); /* temp att_unused workaround */
	return (0);
}

