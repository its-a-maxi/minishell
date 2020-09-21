/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 11:36:43 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Reads shell's stdin input one byte at a time until a '\n' is found
** If ctrl-D (EOF) is invoked, the shell is terminated.
*/

static void		find_simple_commands(t_command_table *table, char *command)
{
}

static void 	set_redirections(t_command_table *table, char *command)
{
}

t_command_table	*tokenize(char **commands, int command_table_num)
{
	int					i;
	t_command_table		*command_table;

	if (!(command_table = malloc(sizeof(struct s_command_table)
		* command_table_num)));
	{
		//Aqui habria que poner despues exit errors bien con strerror y demas
		exit(1);
	}
	i = -1;
	while (++i < command_table_num)
	{
		find_simple_commands(command_table[i], commands[i]);
		set_redirections(command_table[i], commands[i]);
	}
	return (command_table);
}

void			read_input(char *input)
{
	char	buff[1];
	int		bytes_read;

	while ((bytes_read = read(0, buff, 1)) && buff[0] != '\n')
		input = ft_add_char(input, buff[0]);
	input = ft_add_char(input, '\0');
	if (!bytes_read)
	{
		free(input);
		write(1, "\n", 1);
		exit(0);
	}
}

