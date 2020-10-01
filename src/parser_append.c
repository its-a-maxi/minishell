/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:44:02 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/01 13:23:43 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rappnd(t_command_table *table, char ***temp)
{	
	int		i;
	int		j;
	char	*ptr;
	char	*ptr2;

	j = -1;
	i = -1;
	while ((ptr = table->append_file[++i]))
	{
		ptr2 = ptr;
		if (!(ptr = ft_str2chr(ptr, '>')))
			*(*temp + ++j) = ft_strdup(ptr2);
		while ((ptr))
		{
			*ptr = '\0';
			*(*temp + ++j) = ft_strdup(ptr2);
			ptr2 = ptr + 1;
			ptr = ft_str2chr(ptr + 1, '>');
			if (!ptr)
				*(*temp + ++j) = ft_strdup(ptr2);
		}
	}
	full_free((void **)table->append_file, ft_arrlen(table->append_file));
	table->append_file = *temp;
}


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
		rappnd(table, &temp);
	}
}

static int	resize_arr(t_command_table *tb, int j, int n)
{
	char	**temp;

	j = ft_arrlen(tb->append_file);
	temp = malloc(sizeof(char *) * (j + n + 1));
	temp[j + n] = NULL;
	j = -1;
	while (++j < ft_arrlen(tb->append_file))
		temp[j] = ft_strdup(tb->append_file[j]);
	arr_swap(&temp, &tb->append_file);
	return (j - 1);
}

static void	remove_redirect_from_args(t_command_table *tab, int i, int l)
{
	char	**temp;
	int		arrlen;
	int		len;
	int		j;
	int		k;

	len = ft_strlen(tab->simple_commands[l][i]);
	arrlen = ft_arrlen(tab->simple_commands[l]);
	temp = malloc(sizeof(char *) * (arrlen - 1 * (len == 2)));
	temp[arrlen - 1 - 1 * (len == 2)] = NULL;
	k = -1;
	j = -1;
	while (tab->simple_commands[l][++j])
	{
		if ((j == i) || ((j == i + 1) && (len == 2)))
			continue;
		temp[++k] = ft_strdup(tab->simple_commands[l][j]);
	}
	full_free((void **)tab->simple_commands[l], arrlen);
	tab->simple_commands[l] = temp;
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
		appcount = resize_arr(table, j, appcount);
	i = -1;
	while ((ptr = table->simple_commands[j][++i]))
	{
		if ((ft_str2chr(ptr, '>')))
		{
			appcount++;
			table->append_file[appcount] = (ft_strlen(ptr) > 2) ?
			ft_strdup(ptr + 2) : ft_strdup(table->simple_commands
				[j][i + 1]);
printf("\tRemoving redirection from arguments...\n");
			remove_redirect_from_args(table, i, j);
printf("\tRedirections removed.\n\tChecking for parse errors...\n");
			check_redirection_error(table->append_file[appcount]);
printf("\tNo error found.\n");
			i = -1;
		}
	}
printf("\tSplitting the redirection...\n");
	split_append(table);
}
