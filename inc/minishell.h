/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 11:31:21 by aleon-ca         ###   ########.fr       */
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
	char				*input_fd;
	char				*output_fd;
	char				*append_fd;
}						t_command_table;

char					*ft_add_char(char *str, char c);
void					read_input(char *input);

#endif
