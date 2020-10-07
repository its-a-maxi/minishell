/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/07 11:58:21 by aleon-ca         ###   ########.fr       */
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
			ft_split__quots(str, ' '));
		str = tmp + 1;
	}
	tab->simple_commands[++i] = remove_empty_str(
		ft_split__quots(str, ' '));
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
		count[0] = 0;
		count[1] = 0;
		count[2] = 0;
		count_redirections(table->simple_commands[i[0]], count);
		init_redirection_arr(table, i, count);
		set_redirection_arr(table, i);
		if ((check_redirection_error(table, i)))
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
			return (free_errpars(tab, table_num));
		replace_env_var(tab + i);
		j = -1;
		while ((tab[i].simple_commands[++j]))
		{
			remove_quots(&tab[i].simple_commands[j]);
			tab[i].simple_commands[j] =
				remove_empty_str(tab[i].simple_commands[j]);
		}
	}
	full_free((void **)lines, ft_arrlen(lines));
	return (0);
}
