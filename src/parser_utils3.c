/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:29:44 by alejandro         #+#    #+#             */
/*   Updated: 2020/09/30 17:58:23 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	resize_arr(t_command_table *tb, int j, int n, int t)
{
	char	**temp;

	j = (t == 'O') * ft_arrlen(tb->output_file) + (t == 'I') *
		ft_arrlen(tb->input_file) + (t == 'A') * ft_arrlen(tb->append_file);
	temp = malloc(sizeof(char *) * (j + n + 1));
	temp[j + n] = NULL;
	j = -1;
	while (++j < ((t == 'O') * ft_arrlen(tb->output_file) + (t == 'I')
		* ft_arrlen(tb->input_file) + (t == 'A') * ft_arrlen(tb->append_file)))
	{
		if (t == 'O')
			temp[j] = ft_strdup(tb->output_file[j]);
		else if (t == 'I')
			temp[j] = ft_strdup(tb->input_file[j]);
		else
			temp[j] = ft_strdup(tb->append_file[j]);
	}
	if (t == 'O')
		arr_swap(&temp, &tb->output_file); 
	else if (t == 'I')
		arr_swap(&temp, &tb->input_file);
	else
		arr_swap(&temp, &tb->append_file);
	return (j - 1);
}

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

void		setin(t_command_table *table, int j, int incount)
{
	int		i;
	char	*ptr;

	if (!table->input_file)
	{
		table->input_file = malloc(sizeof(char *) * (incount + 1));
		table->input_file[incount] = NULL;
		incount = -1;
	}
	else
		incount = resize_arr(table, j, incount, 'I');
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
			check_redirection_error(table->input_file[incount]);
			i = -1;
		}
	}
}

void		stout(t_command_table *table, int j, int outcount)
{
	int		i;
	char	*ptr;

	if (!table->output_file)
	{
		table->output_file = malloc(sizeof(char *) * (outcount + 1));
		table->output_file[outcount] = NULL;
		outcount = -1;
	}
	else
		outcount = resize_arr(table, j, outcount, 'O');
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
			check_redirection_error(table->output_file[outcount]);
			i = -1;
		}
	}
}

void		stapp(t_command_table *table, int j, int appcount)
{
	int		i;
	char	*ptr;

	if (!table->append_file)
	{
		table->append_file = malloc(sizeof(char *) * (appcount + 1));
		table->append_file[appcount] = NULL;
		appcount = -1;
	}
	else
		appcount = resize_arr(table, j, appcount, 'A');
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
			check_redirection_error(table->append_file[appcount]);
			i = -1;
		}
	}
}
