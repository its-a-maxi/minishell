/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 13:26:33 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In this file we try to parse a general command line of the form:
** 		cmd args | cmd args ... | ... ;
** 		... ;
**		.
**		.
**		.
**		... ;
** 		cmd args | cmd args ... | ... ;
** with any redirection > outfile < infile >> appendfile, before or after
** a command name or argument, for each simple command.
** We parse into a command table for each ';'-terminated sentence.
*/

static void	remove_quots_from_cmd_name(t_command_table *table)
{
	int		i;

	i = -1;
	while (table->simple_commands[++i])
		remove_quots(&table->simple_commands[i][0]);
}

/*
** Finds and sets the simple commands in the command table.
**
** returns: void
**
** parameter #1:		t_command_table		the command table
** parameter #2:		char *				the ';'-terminated line of the table
*/

static void	find_simple_commands(t_command_table *table, char *command_line)
{
	char	**quotpos;
	int		count;
	int		i;
	char	*tmp;

	quotpos = set_quotpos_arr(command_line);
	count = count_not_quoted_char(quotpos, command_line, '|');
	table->simple_commands_num = count + 1;
	if (!(table->simple_commands = malloc(sizeof(char **)
		* (table->simple_commands_num + 1))))
		exit_minishell();
	table->simple_commands[table->simple_commands_num] = NULL;
	i = -1;
	tmp = command_line;
	while ((tmp = ft_strchr__quots(quotpos, command_line, '|')))
	{
		*tmp = '\0';
		table->simple_commands[++i] = remove_empty_str(
			ft_split__quots(command_line, ' '));
		command_line = tmp + 1;
	}
	table->simple_commands[++i] = remove_empty_str(
			ft_split__quots(command_line, ' '));
	remove_quots_from_cmd_name(table);
	free(quotpos);
}

/*
** Sets the output, input and append files for the command table, if any.
**
** returns:	void
**
** parameter #1:	t_command_table		the command table
*/

static void	create_redirection_ptr(t_command_table *tab)
{
	tab->input_files = malloc(sizeof(char **)
		* (tab->simple_commands_num + 1));
	tab->input_files[tab->simple_commands_num] = NULL;
	tab->output_files = malloc(sizeof(char **)
		* (tab->simple_commands_num + 1));
	tab->output_files[tab->simple_commands_num] = NULL;
	tab->append_files = malloc(sizeof(char **)
		* (tab->simple_commands_num + 1));
	tab->append_files[tab->simple_commands_num] = NULL;
	tab->dummy_files = malloc(sizeof(char **)
		* (tab->simple_commands_num + 1));
	tab->dummy_files[tab->simple_commands_num] = NULL;
}

static int	find_redirections(t_command_table *table)
{
	int		i[2];
	int		count[3];

	create_redirection_ptr(table);
	i[0] = -1;
	while (table->simple_commands[++(*i)])
	{
		if (!(table->simple_commands[i[0]]))
			continue ;
		count[0] = 0;
		count[1] = 0;
		count[2] = 0;
		count_redirections(table->simple_commands[i[0]], count);
		init_redirection_arr(table, i, count);
		if (set_redirection_arr(table, i))
			return (1);
	}
	return (0);
}

/*
** Parses the input command line into several command tables, one for each ';'.
**
** return:	t_command_table *		command_table
**
** parameter #1:	char **		input_splitted_by_';'
** parameter #2:	int			number of ';'-terminated sentences
*/

int			tokenize(char **lines, t_command_table *tab, int table_num)
{
	int		i;
	int		j;

	i = -1;
	while (++i < table_num)
	{
		find_simple_commands(tab + i, lines[i]);
		if ((find_redirections(tab + i)))
			return (free_errpars(tab, i, lines));
		replace_env_var(tab + i);
		j = -1;
		while ((tab[i].simple_commands[++j]))
		{
			if ((tab[i].simple_commands[j][0] == NULL)
				&& (tab[i].simple_commands_num > 1))
				return (free_errpars(tab, i, lines));
		}
	}
	free_double(lines);
	return (0);
}
