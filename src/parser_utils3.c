/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:29:44 by alejandro         #+#    #+#             */
/*   Updated: 2020/09/29 13:40:26 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_redirect_from_args(t_command_table *tab, int i, int l, int c)
{
	char	**temp;
	int		arrlen;
	int		len;
	int		j;
	int		k;

	len = ft_strlen(tab->simple_commands[l][i]);
	arrlen = ft_arrlen(tab->simple_commands[l]);
	temp = malloc(sizeof(char *) * (arrlen - 1 * (((len == 1) && (c != 'A'))
		|| ((len == 2) && (c == 'A')))));
	temp[arrlen - 1 - 1 * (((len == 1) && (c != 'A'))
		|| ((len == 2) && (c == 'A')))] = NULL;
	k = -1;
	j = -1;
	while (tab->simple_commands[l][++j])
	{
		if ((j == i) || ((j == i + 1) && (((c == 'A') && (len == 2))
			|| ((c != 'A') && (len == 1)))))
			continue;
		temp[++k] = ft_strdup(tab->simple_commands[l][j]);
	}
	full_free((void **)tab->simple_commands[l], arrlen);
	tab->simple_commands[l] = temp;
}

void		set_inredirect(t_command_table *table, int j, int incount)
{
	int		i;
	char	*ptr;

	if (!table->input_file)
	{
		table->input_file = malloc(sizeof(char *) * (incount + 1));
		table->input_file[incount] = NULL;
		incount = -1;
		i = -1;
		while ((ptr = table->simple_commands[j][++i]))
		{
			if ((ft_strchr(ptr, '<')))
			{
				incount++;
				table->input_file[incount] = (ft_strlen(ptr) != 1) ?
				ft_strdup(ptr + 1) : ft_strdup(table->simple_commands
					[j][i + 1]);
				remove_redirect_from_args(table, i, j, 'I');
				i = -1;
			}
		}
	}
}

void		set_outredirect(t_command_table *table, int j, int outcount)
{
	int		i;
	char	*ptr;

	if (!table->output_file)
	{
		table->output_file = malloc(sizeof(char *) * (outcount + 1));
		table->output_file[outcount] = NULL;
	}
	outcount = -1;
	i = -1;
	while ((ptr = table->simple_commands[j][++i]))
	{	
		if (!(ft_str2chr(ptr, '>')) && (ft_strchr(ptr, '>')))
		{
			outcount++;
			table->output_file[outcount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr + 1) : ft_strdup(table->simple_commands
				[j][i + 1]);
			remove_redirect_from_args(table, i, j, 'O');	
			i = -1;
		}
	}
}

void		set_appredirect(t_command_table *table, int j, int appcount)
{
	int		i;
	char	*ptr;

	if (!table->append_file)
	{
		table->append_file = malloc(sizeof(char *) * (appcount + 1));
		table->append_file[appcount] = NULL;
	}
	appcount = -1;
	i = -1;
	while ((ptr = table->simple_commands[j][++i]))
	{
		if ((ft_str2chr(ptr, '>')))
		{
			appcount++;
			table->append_file[appcount] = (ft_strlen(ptr) > 2) ?
			ft_strdup(ptr + 2) : ft_strdup(table->simple_commands
				[j][i + 1]);
			remove_redirect_from_args(table, i, j, 'A');
			i = -1;
		}
	}
}
