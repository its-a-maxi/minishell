/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/24 12:30:46 by mmonroy-         ###   ########.fr       */
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

#include <libc.h>

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
** simple_command[][] = {name, argument #1, ... argument #n, NULL}
*/

typedef struct			s_command_table
{
	char				***simple_commands;
	int					simple_commands_num;
	char				*input_file;
	char				*output_file;
	char				*append_file;
}						t_command_table;

/*
** General Env variables
*/
char					**g_env;

/*
** parser_utils2.c
*/
char					**remove_empty_str(char **arr);
char					**ft_split_and_quotations(char *str, char c);
/*
** parser_utils.c
*/
void					free_command_tables(t_command_table *table, int num);
char					*ft_str2chr(char *str, char c);
char					*ft_add_char(char *str, char c);
void					read_input(char **input);
void					set_redirect(t_command_table *t, char *str, char type);
/*
** parser.c
*/
struct s_command_table	*tokenize(char **command_lines, int table_num);
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
void					cmd_export(char **argv);
#endif
