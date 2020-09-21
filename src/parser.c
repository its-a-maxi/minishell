/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 13:20:13 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In this file we try to parse a general command line of the form:
** 		cmd args | cmd args ... | ... > outfile < infile >> appendfile;
** 		... ;
**		... ;
** 		cmd args | cmd args ... | ... > outfile < infile >> appendfile;
** into a command table for each ';'-terminated sentence,
** and each command table into its simple commands constituents (cmd args).
*/

/*
** Finds the total number of simple commands in the command table
** and sets their names ,arguments and argument number.
**
** returns:	void
**
** parameter #1:	t_command_table		table
** parameter #2:	char *				command_line
*/

static void		find_simple_commands(t_command_table table, char *command_line)
{
	int		i;
	char	*pipe_pos;

	table.simple_commands_num = ft_strnchr(command_line, '|') + 1;
	table.commands = malloc(sizeof(struct s_simple_command)
		* table.simple_commands_num);
	i = -1;
	while (++i < table.simple_commands_num)
	{
	}
	//Puede haber espacios hasta los argumentos
	//Simple commands separados por |
}

/*
** Sets the output, input and append files for the command table, if any.
**
** returns:	void
**
** parameter #1:	t_command_table		table
** parameter #2:	char *				command_line
*/

static void		set_redirections(t_command_table *table, char *command_line)
{
	//Puede haber espacios hasta el file
}

/*
** Parses the input command line into several command tables, one for each ';'.
**
** return:	t_command_table *		command_table
**
** parameter #1:	char **		input_splitted_by_';'
** parameter #2:	int			number of ';'-terminated sentences
*/

t_command_table	*tokenize(char **commands, int command_table_num)
{
	int					i;
	t_command_table		*command_table;

	if (!(command_table = malloc(sizeof(struct s_command_table)
		* command_table_num)))
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
	free(commands);
	return (command_table);
}
