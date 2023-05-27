#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFERSIZE 128
#define TOKEN_DELIM " \t\r\n\a"

extern char **environ;


/**
 * struct shell_data -> this is the struct that  will
 * contains all important shell data on application runtime
 * @argv: argument vector, array of argument passed
 * @input: This is the command line given to the shell by the user
 * @args: This a null terminated array of tokens of the given input
 * @status: A numeric value of the status of the shell last process
 * @counter: this is the submission of process in the shell
 * @_environ: the shell environment variables
 * @pid: the process ID of the shell
 */
typedef struct shell_data
{
	char **argv;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} st_shell;

/**
 * struct separator_lists - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separator_lists
{
	char separator;
	struct separator_lists *next;
} st_separtor_list;

/**
 * struct command_lines_list - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct command_lines_list
{
	char *line;
	struct command_lines_list *next;
} sh_command_line;

/**
 * struct variable_lists - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct variable_lists
{
	int len_var;
	char *val;
	int len_val;
	struct variable_lists *next;
} sh_variable_list;

/**
 * struct builtin_struct - The "builtin_struct" structure is used
 * to represent built-in command arguments.
 * @function_name: the name of the built-in command.
 * @function: a pointer to a function with unspecified
 * return type and parameters.
 */
typedef struct builtin_struct
{
	char *function_name;
	int (*function)(st_shell *s_datas);
} builtin_function;

void shell_prompt(void);

void _memcpy(void *dest, const void *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

char *_strdup(const char *str);
int _strlen(const char *str);
char *_strtok(char str[], char *delim);
int _isdigit(const char *s);
int count_char(char *input, int index);
int num_len(int n);
char *aux_itoa(int nunber);
void get_sigint(int sig);
int _atoi(char *string);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
void _strncpy(char *dest, char *src, size_t n);
void string_slice(char *str, int start, int end, char *result);
char *_strchr(char *s, char c);
void rev_string(char *s);

char *filter_out_comment(char *in);
void shell_loop(st_shell *s_datas);
char *read_line(int *eof);

void free_data(st_shell *s_datas);
void set_data(st_shell *s_datas, char **argv);

st_separtor_list *add_sep_end(st_separtor_list **head, char seperatorFF);
void free_st_separtor_list(st_separtor_list **head);
sh_command_line *add_line_end(sh_command_line **head, char *line);
void free_sh_command_line(sh_command_line **head);

sh_variable_list *add_var_end(sh_variable_list **head,
int length_var, char *var, int length_val);
void free_var_list(sh_variable_list **head);

char *char_switch(char *input, int flag);
void join_nodes(st_separtor_list **head_s,
sh_command_line **head_l, char *input);
void next_command(st_separtor_list **list_s,
sh_command_line **list_l, st_shell *s_datas);
int tokenize_commands(st_shell *s_datas, char *input);
char **tokenize_input(char *input);

int verify_variable(sh_variable_list **head, char *input, char *s_last, st_shell *data);
char *sub_input(sh_variable_list **head,
char *input, char *new_input, int size);
char *swap_variable(char *input, st_shell *s_datas);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);
void help(void);
void help_alias(void);
void help_cd(void);
int get_help(st_shell *s_datas);

int locate_command(st_shell *s_datas);
int current_location(char *path, int *i);
char *get_location(char *cmd, char **_environ);
int runable(st_shell *s_datas);
int verify_cmd_error(char *dir, st_shell *s_datas);
int run_command(st_shell *s_datas);
void cd_parent(st_shell *s_datas);
void cd_to(st_shell *s_datas);
void cd_previous(st_shell *s_datas);
void cd_home(st_shell *s_datas);
int manage_cd(st_shell *s_datas);
int (*shell_builtin(char *command))(st_shell *s_datas);
int exit_command(st_shell *s_datas);

char *_mygetenv(const char *name, char **_environ);
int _myenv(st_shell *s_datas);
int cmp_env_name(const char *nenv, const char *name);
char *copy_info(char *name, char *variable);
void set_myenv(char *name, char *value, st_shell *s_datas);
int set_myenv_wrapper(st_shell *s_datas);
int _unsetenv(st_shell *s_datas);
void environ_var_check(sh_variable_list **head, char *input, st_shell *data);

char *error_get_cd(st_shell *s_datas);
char *error_not_found(st_shell *s_datas);
char *error_exit_shell(st_shell *s_datas);
char *error_env(st_shell *s_datas);
char *error_path_126(st_shell *s_datas);
int find_first_non_whitespace(char *input, int *index);
int find_next_operator_index(char *input, int *index);
int error_info(st_shell *s_datas, int eval);
int locate_syntax_error(char *input, int index, char last);
void display_syn_error(st_shell *s_datas, const char *input, int i, int flag);
int syntax_error(st_shell *s_datas, char *input);

#endif
