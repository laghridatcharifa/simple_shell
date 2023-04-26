#include "shell.h"

/**
 * input_buf - fnction ssize_t
 * @m: struct infop
 * @bf: chacter one
 * @lv: character two
 *
 * Return: returning siez_t
 */
ssize_t input_buf(infop *m, char **bf, size_t *lv)
{
	ssize_t v = 0;
	size_t lv_p = 0;

	if (!*lv) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)i->buf_cmd);*/
		free(*bf);
		*bf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &lv_p, stdin);
#else
		v = _getline(m, bf, &lv_p);
#endif
		if (v > 0)
		{
			if ((*bf)[v - 1] == '\n')
			{
				(*bf)[v - 1] = '\0'; /* remove trailing newline */
				v--;
			}
			m->lf = 1;
			remove_comments(*bf);
			build_history_list(m, *bf, m->hc++);
			/* if (_strchr(*bf, ';')) is this a command chain? */
			{
				*lv = v;
				m->buf_cmd = bf;
			}
		}
	}
	return (v);
}

/**
 * get_input - function get input
 * @i: struct infop
 * * Return: reutning ssize t
 */
ssize_t get_input(infop *i)
{
	static char *bf;
	static size_t a, b, lv;
	ssize_t v = 0;
	char **bp = &(i->a), *pp;

	_putchar(BUF_FLUSH);
	v = input_buf(i, &bf, &lv);
	if (v == -1) /* EOF */
		return (-1);
	if (lv)
	{
		b = a;
		pp = bf + a;

		check_chain(i, bf, &b, a, lv);
		while (b < lv) /* iterate to semicolon or end */
		{
			if (is_chain(i, bf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= lv) /* reached end of buffer? */
		{
			a = lv = 0; /* reset position and length */
			i->type_cmd = CMD_NORM;
		}

		*bp = pp;
		return (_strlen(pp));
	}

	*bp = bf;
	return (v);
}

/**
 * read_buf - function to reads
 * @i: struct infop
 * @bf: string buffer
 * @s: size_t size
 *
 * Return: return size
 */
ssize_t read_buf(infop *i, char *bf, size_t *s)
{
	ssize_t m = 0;

	if (*s)
		return (0);
	m = read(i->rfd, bf, READ_BUF_SIZE);
	if (m >= 0)
		*s = m;
	return (m);
}

/**
 * _getline - function to get line
 * @i: struct infop
 * @pt: pointer
 * @len: size
 * Return: return int
 */
int _getline(infop *i, char **pt, size_t *len)
{
	static char bf[READ_BUF_SIZE];
	static size_t a, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL;
	char *new = NULL;
	char *c;

	p = *pt;
	if (p && len)
		s = *len;
	if (a == l)
		a = l = 0;

	r = read_buf(i, bf, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(bf + a, '\n');
	k = c ? 1 + (unsigned int)(c - bf) : l;
	new = _realloc(p, s, s ? s + k : k + 1);
	if (!new) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new, bf + a, k - a);
	else
		_strncpy(new, bf + a, k - a + 1);

	s += k - a;
	a = k;
	p = new;

	if (len)
		*len = s;
	*pt = p;
	return (s);
}

/**
 * sigintHandler -function sing in
 * @sig_num: the sing number
 *
 * Return: return void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

