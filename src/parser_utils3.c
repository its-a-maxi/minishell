/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:29:44 by alejandro         #+#    #+#             */
/*   Updated: 2020/09/29 10:19:49 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_redirect_from_args(t_command_table *table, int i, int c)
{
	char	**temp;
	int		arrlen;
	int		len;
	int		j;
	int		k;

	len = ft_strlen(table->simple_commands[table->simple_commands_num - 1][i]);
	arrlen = ft_arrlen(table->simple_commands[table->simple_commands_num - 1]);
	temp = malloc(sizeof(char *) * (arrlen - 1 * (((len == 1) && (c != 'A'))
		|| ((len == 2) && (c == 'A')))));
	temp[arrlen - 1 - 1 * (((len == 1) && (c != 'A'))
		|| ((len == 2) && (c == 'A')))] = NULL;
//printf("\tLast simple_command array length after removing redirections is %d.\n", 
//	arrlen - 1 - 1 * (((len == 1) && (c != 'A'))
//		|| ((len == 2) && (c == 'A'))));
	k = -1;
	j = -1;
	while (table->simple_commands[table->simple_commands_num - 1][++j])
	{
		if ((j == i) || ((j == i + 1) && (((c == 'A') && (len == 2))
			|| ((c != 'A') && (len == 1)))))
			continue;
		temp[++k] = ft_strdup(
			table->simple_commands[table->simple_commands_num - 1][j]);
	}
//printf("\tRemoved redirection from args. Now last simple_command array is:\n");
	full_free((void **)table->simple_commands[table->simple_commands_num - 1],
		arrlen);
	table->simple_commands[table->simple_commands_num - 1] = temp;
//int l = -1;while (table->simple_commands[table->simple_commands_num - 1][++l]){printf("\t%s\n", table->simple_commands[table->simple_commands_num - 1][l]);}
}

void		set_inredirect(t_command_table *table, int incount)
{
	int	i;
	char	*ptr;

	table->input_file = malloc(sizeof(char *) * (incount + 1));
	table->input_file[incount] = NULL;
	incount = -1;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{
		if ((ft_strchr(ptr, '<')))
		{
			incount++;
			table->input_file[incount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr + 1) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'I');
			i = -1;
		}
	}
}

void		set_outredirect(t_command_table *table, int outcount)
{
	int	i;
	char	*ptr;

	table->output_file = malloc(sizeof(char *) * (outcount + 1));
	table->output_file[outcount] = NULL;
	outcount = -1;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{	
		if (!(ft_str2chr(ptr, '>')) && (ft_strchr(ptr, '>')))
		{
			outcount++;
			table->output_file[outcount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr + 1) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'O');	
			i = -1;
		}
	}
}

void		set_appredirect(t_command_table *table, int appcount)
{
	int	i;
	char	*ptr;

	table->append_file = malloc(sizeof(char *) * (appcount + 1));
	table->append_file[appcount] = NULL;
	appcount = -1;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{
		if ((ft_str2chr(ptr, '>')))
		{
			appcount++;
			table->append_file[appcount] = (ft_strlen(ptr) > 2) ?
			ft_strdup(ptr + 2) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'A');
			i = -1;
		}
	}
}

static void	split_remaining_redirections(t_command_table *table)
{
}
