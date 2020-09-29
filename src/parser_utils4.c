/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 10:29:56 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/29 13:28:23 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_append(t_command_table *table)
{
	char	*ptr;
	int		i;
	int		incount;
	char	**temp;

	incount = 0;
	i = -1;
	while (table->append_file[++i])
	{
		ptr = table->append_file[i];
		while ((ptr = ft_str2chr(ptr, '>')))
		{
			incount++;
			ptr++;
		}	
	}
	if ((incount))
	{
		temp = malloc(sizeof(char *) * (ft_arrlen(table->append_file)
			+ incount + 1));
		temp[ft_arrlen(table->append_file) + incount] = NULL;
		replace_appnd_arr(table, &temp);
	}
}

static void	split_output(t_command_table *table)
{
	char	*ptr;
	int		i;
	int		incount;
	char	**temp;

	incount = 0;
	i = -1;
	while (table->output_file[++i])
	{
		ptr = table->output_file[i];
		while ((ptr = ft_strchr(ptr, '>')) && !(ft_str2chr(ptr, '>')))
		{
			incount++;
			ptr++;
		}	
	}
	if ((incount))
	{
		temp = malloc(sizeof(char *) * (ft_arrlen(table->output_file)
			+ incount + 1));
		temp[ft_arrlen(table->output_file) + incount] = NULL;
		replace_outpt_arr(table, &temp);
	}
}

static void	split_input(t_command_table *table)
{
	char	*ptr;
	int		i;
	int		incount;
	char	**temp;

	incount = 0;
	i = -1;
	while (table->input_file[++i])
	{
		ptr = table->input_file[i];
		while ((ptr = ft_strchr(ptr, '<')))
		{
			incount++;
			ptr++;
		}
	}
	if ((incount))
	{
		temp = malloc(sizeof(char *) * (ft_arrlen(table->input_file)
			+ incount + 1));
		temp[ft_arrlen(table->input_file) + incount] = NULL;
		replace_input_arr(table, &temp);
	}
}

void		split_remaining_redirections(t_command_table *table)
{
	if (table->input_file)
		split_input(table);
	if (table->output_file)
		split_output(table);
	if (table->append_file)
		split_append(table);
}
