/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/30 09:43:31 by aleon-ca         ###   ########.fr       */
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
** into a command table for each ';'-terminated sentence.
*/

/*
** Finds and sets the simple commands in the command table.
**
** returns: void
**
** parameter #1:		t_command_table		the command table
** parameter #2:		char *				the ';'-terminated line of the table
*/

static void	find_next_simple_command(t_command_table *tab, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = str;
	while ((tmp = ft_strchr(str, '|')))
	{
		*tmp = '\0';
		tab->simple_commands[++i] = remove_empty_str(
			ft_split_and_quotations(str, ' '));
		str = tmp + 1;
	}
	tab->simple_commands[++i] = remove_empty_str(
		ft_split_and_quotations(str, ' '));
}


/*
** Finds the total number of simple commands in the command table
**
** returns:	void
**
** parameter #1:	t_command_table		the command table
** parameter #2:	char *				the ';'-terminated line of the table
*/

static void	find_simple_commands(t_command_table *table, char *command_line)
{
	table->simple_commands_num = ft_strnchr(command_line, '|') + 1;
	if (!(table->simple_commands = malloc(sizeof(char **)
		* (table->simple_commands_num + 1))))
		exit_minishell();
	table->simple_commands[table->simple_commands_num] = NULL;
	find_next_simple_command(table, command_line);
}

/*
** Sets the output, input and append files for the command table, if any.
**
** returns:	void
**
** parameter #1:	t_command_table		the command table
** parameter #2:	char *				the ';'-terminated line of the table
*/

static void	set_redirections(t_command_table *table)
{
	char	*ptr;
	int		i[2];
	int		incount;
	int		outcount;
	int		appcount;

	table->input_file = NULL;
	table->output_file = NULL;
	table->append_file = NULL;
	i[1] = -1;
	while (table->simple_commands[++i[1]])
	{
		incount = 0;
		outcount = 0;
		appcount = 0;
		i[0] = -1;
printf("Checking for redirections in command %d\n", i[1]);
		while ((ptr = table->simple_commands[i[1]][++i[0]]))
		{
			if ((ft_strchr(ptr, '<')))
				incount++;
			else if ((ft_str2chr(ptr, '>')))
				appcount++;
			else if ((ft_strchr(ptr, '>')))
				outcount++;
		}
printf("Found %d input_files; %d output_files; %d append_files\n", incount, outcount, appcount);
printf("Entering set_indirect...\n");
		set_inredirect(table, i[1], incount);
printf("set_indirect successful.\nEntering set_outdirect...\n");
		set_outredirect(table, i[1], outcount);
printf("set_outdirect successful.\nEntering set_appdirect...\n");
		set_appredirect(table, i[1], appcount);
printf("set_appdirect successful.\n");
		split_remaining_redirections(table);
printf("Redirection parsing ended.\n");	
	}
}

/*
** Parses the input command line into several command tables, one for each ';'.
**
** return:	t_command_table *		command_table
**
** parameter #1:	char **		input_splitted_by_';'
** parameter #2:	int			number of ';'-terminated sentences
*/

t_command_table	*tokenize(char **command_lines, int command_table_num)
{
	int					i;
	t_command_table		*command_table;

	if (!(command_table = malloc(sizeof(struct s_command_table)
		* command_table_num)))
		exit_minishell();
	i = -1;
	while (++i < command_table_num)
	{
		find_simple_commands(command_table + i, command_lines[i]);
		set_redirections(command_table + i);
	}
printf("Ended the parsing\n");
	full_free((void **)command_lines, ft_arrlen(command_lines));
	return (command_table);
}
