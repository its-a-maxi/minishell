/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 12:49:53 by aleon-ca         ###   ########.fr       */
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
# include "../libft/inc/libft.h"

/*
** The t_simple_commands struct contains the name and arguments of
** an input command:
**
** command_name arguments[1] ... arguments[n]
*/

typedef struct			s_simple_command
{
	char				*command_name;
	char				**arguments;
	int					arguments_num;
}						t_simple_command;

/*
** The t_command_table struct contains the information of a set of
** input commands, i.e, some input line of the form:
**
** command_name arguments | command_name2 ... | ... > output > input >> append;
**
** which we will use to stablish the correct pipe and redirection relations
** between commands.
*/

typedef struct			s_command_table
{
	t_simple_command	*commands;
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
** parser_utils.c
*/
char					*ft_add_char(char *str, char c);
void					read_input(char *input);

/*
** parser.c
*/
struct s_command_table	tokenize(char **command_lines, int table_num);
/*
** executor.c
*/
void					executor(t_command_table *table, int table_num);
/*
** env_handler.c
*/
void					save_env(int argc, char **argv, char **envp);
#endif
