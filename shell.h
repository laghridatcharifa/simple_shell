#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct node - singly linked list
 * @number: the number
 * @s: a string
 * @next: points to the next node
 */
typedef struct node
{
	int number;
	char *s;
	struct node *next;
} node_l;

/**
 * struct infopass - infopass into a function,
 * allowing uniform prototype for function pointer struct
 * @a: a string contain arguements
 * @ar:an array of strings from a
 * @p: a string path
 * @ac: the count argument
 * @lc: the  count error
 * @en:  exit()s error code
 * @lf: if on count this line of input
 * @fn: name of the program
 * @vn: linked environ
 * @envi: custom modified copy of environ from LL env
 * @h: the history
 * @ai: alias node
 * @chang_ev: in case the environ change
 * @s: the return status of the execed command
 * @buf_cmd: address of pointer to buf_cmd, on if chaining
 * @type_cmd: CMD_type ||, &&, ;
 * @rfd: the fd from which to read line input
 * @hc: the history line number count
 */
typedef struct infopass
{
	char *a;
	char **ar;
	char *p;
	int ac;
	unsigned int lc;
	int en;
	int lf;
	char *fn;
	node_l *vn;
	node_l *h;
	node_l *ai;
	char **envi;
	int chang_ev;
	int s;

	char **buf_cmd; /* pointer to cmd ; chain buffer, for memory mangement */
	int type_cmd; /* type_cmd ||, &&, ; */
	int rfd;
	int hc;
} infop;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct bt - contains a bt string and related function
 * @t: the bt command flag
 * @fu: the function
 */
typedef struct bt
{
	char *t;
	int (*fu)(infop *);
} tableb;


/* toem_shloop.c */
int hsh(infop *, char **);
int find_bt(infop *);
void find_cmd(infop *);
void fork_cmd(infop *);

/* toem_parser.c */
int is_cmd(infop *, char *);
char *dup_chars(char *, int, int);
char *find_path(infop *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(infop *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(infop *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_bt.c */
int _myexit(infop *);
int _mycd(infop *);
int _myhelp(infop *);

/* toem_bt1.c */
int _myhistory(infop *);
int _myalias(infop *);

/*toem_getline.c */
ssize_t get_input(infop *);
int _getline(infop *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(infop *);
void set_info(infop *, char **);
void free_info(infop *, int);

/* toem_environ.c */
char *_getenv(infop *, const char *);
int _myenv(infop *);
int _mysetenv(infop *);
int _myunsetenv(infop *);
int populate_env_list(infop *);

/* toem_getenv.c */
char **get_environ(infop *);
int _unsetenv(infop *, char *);
int _setenv(infop *, char *, char *);

/* toem_history.c */
char *get_history_file(infop *info);
int write_history(infop *info);
int read_history(infop *info);
int build_history_list(infop *info, char *buf, int linecount);
int renumber_history(infop *info);

/* toem_lists.c */
node_l *add_node(node_l **, const char *, int);
node_l *add_node_end(node_l **, const char *, int);
size_t print_list_str(const node_l *);
int delete_node_at_index(node_l **, unsigned int);
void free_list(node_l **);

/* toem_lists1.c */
size_t list_len(const node_l *);
char **node_lo_strings(node_l *);
size_t print_list(const node_l *);
node_l *node_starts_with(node_l *, char *, char);
ssize_t get_node_index(node_l *, node_l *);

/* toem_vars.c */
int is_chain(infop *, char *, size_t *);
void check_chain(infop *, char *, size_t *, size_t, size_t);
int replace_alias(infop *);
int replace_vars(infop *);
int replace_string(char **, char *);

#endif

