/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/01 17:30:08 by alejandro        ###   ########.fr       */
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
** parameter #2:	char *				the ';'-terminated line of the table
*/

static void	find_redirect(char *ptr, int *count)
{
	if ((ft_strchr(ptr, '<')))
		++count[0];
	else if ((ft_str2chr(ptr, '>')))
		++count[2];
	else if ((ft_strchr(ptr, '>')))
		++count[1];
}

static int	set_redirections(t_command_table *table)
{
	char	*ptr;
	int		i[2];
	int		count[3];

	i[1] = -1;
	initr(table, i[1], count);
	while (table->simple_commands[++i[1]])
	{//init_redirect irá aquí cuando se ponga ***input_file
		count[0] = 0;
		count[1] = 0;
		count[2] = 0;
		i[0] = -1;
		while ((ptr = table->simple_commands[i[1]][++i[0]]))
			find_redirect(ptr, count);
		if ((setin(table, i[1], count[0])) || (stout(table, i[1],
			count[1])) || (stapp(table, i[1], count[2])))
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

int		tk(char **lines, t_command_table *tab, int table_num)
{
	int					i;

	i = -1;
	while (++i < table_num)
	{
		find_simple_commands(tab + i, lines[i]);
		if ((set_redirections(tab + i)))
			return (free_errpars(tab, table_num));
		replace_env_var(tab + i);
	}
printf("Ended the parsing\n");
	full_free((void **)lines, ft_arrlen(lines));
	return (0);
}
