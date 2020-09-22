/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/22 10:08:38 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In this file we try to parse a general command line of the form:
** 		cmd args | cmd args ... | ... > outfile < infile >> appendfile;
** 		... ;
**		.
**		.
**		.
**		... ;
** 		cmd args | cmd args ... | ... > outfile < infile >> appendfile;
** into a command table for each ';'-terminated sentence,
** and each command table into its simple command constituyents (cmd args).
*/


/*
** Finds the next simple command name in the command table line, and sets
** its arguments.
** If there are pipes, (simple_commands_num > 1), it moves the line pointer to
** the position after the pipe.
**
** returns: void
**
** parameter #1:		t_command_table		the command table
** parameter #2:		int					number of simple commands in table
** parameter #3:		char *				the ';'-terminated line of the table
*/

static void		find_next_simple_command(t_command_table *tab, int n, char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i] == ' ')
		;
	j = i;
	str[j] = '\0';
	table->commands[n].command_name = ft_strdup(str);
	if (tab->simple_commands_num > 1)
	{
		while (str[++i] != '|')
			;
		str[i] = '\0';
		//Mejorar esto despues xq split puede dar strings vacias
		//en el caso echo' '' 'hola -> args serian:
		//args[0] = null; args[1] = hola; y daria args_num = 2 en vez de 1
		tab->commands[n].arguments = ft_split(str + j + 1, ' ');
		str += i + 1;
	}
	else
	{
		while ((str[++i] != '<') && (str[i] != '>') && (str[i]))
			;
		str[i] = '\0';
		//Mismo asunto
		tab->commands[n].arguments = ft_split(str + j + 1, ' ');
	}
	tab->commands[n].arguments_num = ft_arrlen(tab->commands[n].arguments);
}


/*
** Finds the total number of simple commands in the command table
** and sets their names ,arguments and argument number.
**
** returns:	void
**
** parameter #1:	t_command_table		the command table
** parameter #2:	char *				the ';'-terminated line of the table
*/

static void		find_simple_commands(t_command_table *table, char *command_line)
{
	int		i;
	char	*pipe_pos;

	table->simple_commands_num = ft_strnchr(command_line, '|') + 1;
	table->commands = malloc(sizeof(struct s_simple_command)
		* table->simple_commands_num);
	i = -1;
	while (++i < table->simple_commands_num)
		find_next_simple_command(table, i, command_line);
}

/*
** Sets the output, input and append files for the command table, if any.
**
** returns:	void
**
** parameter #1:	t_command_table		the command table
** parameter #2:	char *				the ';'-terminated line of the table
*/

static void		set_redirections(t_command_table *table, char *command_line)
{
	//Puede haber espacios hasta el file
	//Puede no haber espacios: echo hola>infile funciona
	char		*ptr1;
	char		*ptr2;
	int			i;

	i = -1;
	ptr2 = ft_strchr(command_line, '<');
	if ((ptr2))
		set_input_redirection(table, command_line);
	ptr1 = ft_strchr(command_line, '>');
	if ((ptr1) && (ptr1 + 1) != '>')
		set_output_redirection(table, command_line);
	else if ((ptr1) && (ptr + 1) == '>')
		set_append_redirection(table, command_line);
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
		set_redirections(command_table + i, commands[i]);
		find_simple_commands(command_table + i, commands[i]);
	}
	full_free((void **)commands, ft_arrlen(commands));
	return (command_table);
}
