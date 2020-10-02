/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:25:28 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/01 17:21:05 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rinput(t_command_table *table, char ***temp)
{
	int		i;
	int		j;
	char	*ptr;
	char	*ptr2;

	j = -1;
	i = -1;
	while ((ptr = table->input_file[++i]))
	{
		ptr2 = ptr;
		if (!(ptr = ft_strchr(ptr, '<')))
			*(*temp + ++j) = ft_strdup(ptr2);
		while ((ptr))
		{
			*ptr = '\0';
			*(*temp + ++j) = ft_strdup(ptr2);
			ptr2 = ptr + 1;
			ptr = ft_strchr(ptr + 1, '<');
			if (!ptr)
				*(*temp + ++j) = ft_strdup(ptr2);
		}
	}
	full_free((void **)table->input_file, ft_arrlen(table->input_file));
	table->input_file = *temp;
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
		rinput(table, &temp);
	}
}

static int	resize_arr(t_command_table *tb, int j, int n)
{
	char	**temp;

	j = ft_arrlen(tb->input_file);
	temp = malloc(sizeof(char *) * (j + n + 1));
	temp[j + n] = NULL;
	j = -1;
	while (++j < ft_arrlen(tb->input_file))
		temp[j] = ft_strdup(tb->input_file[j]);
	arr_swap(&temp, &tb->input_file);
	return (j - 1);
}

void		rmin(t_command_table *tab, int i, int l)
{
	char	**temp;
	int		arrlen;
	int		len;
	int		j;
	int		k;

	len = ft_strlen(tab->simple_commands[l][i]);
	arrlen = ft_arrlen(tab->simple_commands[l]);
	temp = malloc(sizeof(char *) * (arrlen - 1 * (len == 1)));
	temp[arrlen - 1 - 1 * (len == 1)] = NULL;
	k = -1;
	j = -1;
	while (tab->simple_commands[l][++j])
	{
		if ((j == i) || ((j == i + 1) && (len == 1)))
			continue;
		temp[++k] = ft_strdup(tab->simple_commands[l][j]);
	}
	full_free((void **)tab->simple_commands[l], arrlen);
	tab->simple_commands[l] = temp;
}

int		setin(t_command_table *t, int j, int n)
{
	if (!t->input_file)
	{
		t->input_file = malloc(sizeof(char *) * (n + 1));
		t->input_file[n] = NULL;
		n = -1;
	}
	else
		n = resize_arr(t, j, n);
	if ((uptin(t, j, n)))
		return (1);
	split_input(t);
	return (0);
}
