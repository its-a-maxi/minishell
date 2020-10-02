/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/01 17:26:13 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

#include <libc.h>

# define EREDIR "minishell: parse error near a redirection.\n"
/*
** The t_command_table struct contains the information of a set of
** input commands, i.e, some input line of the form:
**
** command_name arguments | command_name2 ... | ... > output > input >> append;
**
** which we will use to stablish the correct pipe and redirection relations
** between commands.
** The simple_commands contain the name and arguments of
** an input command:
**
** simple_commands[][] = {name, argument #1, ... argument #n, NULL}
*/

typedef struct			s_command_table
{
	char				***simple_commands;
	int					simple_commands_num;
	char				**input_file;
	char				**output_file;
	char				**append_file;
}						t_command_table;

/*
** General Env variables
*/
char					**g_env;
/*
** parser_error.c
*/
int					free_errpars(t_command_table *t, int i);
int					check_redirection_error(char *str);
/*
** parser_input.c
*/
int					setin(t_command_table *t, int j, int n);
void					rmin(t_command_table *t, int j, int n);
/*
** parser_output.c
*/
int					stout(t_command_table *t, int j, int n);
void					rmout(t_command_table *t, int j, int n);
/*
** parser_append.c
*/
int					stapp(t_command_table *t, int j, int n);
void					rmapp(t_command_table *t, int j, int n);

/*
** parser_utils4.c
*/
int					uptin(t_command_table *t, int j, int n);
int					upout(t_command_table *t, int j, int n);
int					upapp(t_command_table *t, int j, int n);
/*
** parser_utils3.c
*/
void					replace_env_var(t_command_table *table);
void					arr_swap(char ***dst,  char ***src);
void					initr(t_command_table *t, int i, int *n);
/*
** parser_utils2.c
*/
char					**remove_empty_str(char **arr);
char					**ft_split__quots(char *str, char c);
/*
** parser_utils.c
*/
void					freetb(t_command_table *table, int num);
char					*ft_str2chr(char *str, char c);
char					*ft_add_char(char *str, char c);
void					read_input(char **input);
/*
** parser.c
*/
int					tk(char **a, t_command_table *t, int n);
/*
** executor.c
*/
void					executor(t_command_table *table, int table_num);
/*
** env_handler.c
*/
void					save_env(int argc, char **argv, char **envp);
void					exit_minishell(void);
char					*env_selector(char *env);
int						envp_len(char **envp);
/*
** cmd_cd.c
*/
int						cmd_cd(char **arg);
/*
** cmd_env.c
*/
void    				cmd_env(char **arg);
/*
** cmd_echo.c
*/
void					cmd_echo(char **argv);
/*
** cmd_pwd.c
*/
void					cmd_pwd(char **arg);
/*
** cmd_export.c
*/
void					cmd_export(char **arg);
/*
** cmd_unset.c
*/
void            		cmd_unset(char **arg);
#endif
