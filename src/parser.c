/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:13:35 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/22 12:32:01 by aleon-ca         ###   ########.fr       */
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

static void		split_till_redirection(t_command_table *tab, char *str)
{
	char	*inptr;
	char	*outptr;
	char	tmp;

	if ((inptr = ft_strchr(str, '<')) < (outptr = ft_strchr(str, '>')))
	{
		tmp = *inptr;
		*inptr = '\0';
		tab->simple_commands[++i] = ft_split(str, ' ');
		*inptr = tmp;
	}
	else
	{
		tmp = *outptr;
		*outptr = '\0';
		tab->simple_commands[++i] = ft_split(str, ' ');
		*outptr = tmp;
	}
}

}

/*
** Finds and sets the simple commands in the command table.
**
** returns: void
**
** parameter #1:		t_command_table		the command table
** parameter #3:		char *				the ';'-terminated line of the table
*/

static void		find_next_simple_command(t_command_table *tab, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = str;
	while ((tmp = ft_strchr(str, '|')))
	{
		*tmp = '\0';
		tab->simple_commands[++i] = ft_split(str, ' ');
		str = tmp + 1;
	}
	if ((tab->input_file) || (tab->output_file) || (tab->append_file))
		split_till_redirection(tab, str);
	else
		tab->simple_commands[++i] = ft_split(str, ' ');
}


/*
** Finds the total number of simple commands in the command table
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
	if (!(table->simple_commands = malloc(sizeof(char **)
		* table->simple_commands_num)))
		exit_shell();
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

static void		set_redirections(t_command_table *table, char *command_line)
{
	//Puede haber espacios hasta el file
	//Puede no haber espacios: echo hola>infile funciona
	char		*ptr1;
	char		*ptr2;
	int			i;

	table->input_file = NULL;
	table->output_file = NULL;
	table->append_file = NULL;
	i = -1;
	ptr2 = ft_strchr(command_line, '<');
	if ((ptr2) && (ptr2 > ft_strchr(command_line, '|')))
		set_redirect(table, ptr2, "input");
	ptr1 = ft_strchr(command_line, '>');
	if ((ptr1) && (ptr1 + 1) != '>'(ptr1 > ft_strchr(command_line, '|')))
		set_redirect(table, command_line, "output");
	else if ((ptr1) && (ptr + 1) == '>'(ptr1 > ft_strchr(command_line, '|')))
		set_redirect(table, ptr1, "append");
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
		set_redirections(command_table + i, command_lines[i]);
		find_simple_commands(command_table + i, command_lines[i]);
	}
	full_free((void **)command_lines, ft_arrlen(command_lines));
	return (command_table);
}
