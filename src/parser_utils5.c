/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 10:41:34 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/29 11:52:10 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_appnd_arr(t_command_table *table, char ***temp)
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

void		replace_outpt_arr(t_command_table *table, char ***temp)
{	
	int		i;
	int		j;
	char	*ptr;
	char	*ptr2;

	j = -1;
	i = -1;
	while ((ptr = table->output_file[++i]))
	{
		ptr2 = ptr;
		if (!(ptr = ft_strchr(ptr, '>')))
			*(*temp + ++j) = ft_strdup(ptr2);
		while ((ptr) && !(ft_str2chr(ptr, '>')))
		{
			*ptr = '\0';
			*(*temp + ++j) = ft_strdup(ptr2);
			ptr2 = ptr + 1;
			ptr = ft_strchr(ptr + 1, '>');
			if (!ptr)
				*(*temp + ++j) = ft_strdup(ptr2);
		}
	}
	full_free((void **)table->output_file, ft_arrlen(table->output_file));
	table->output_file = *temp;
}

void		replace_input_arr(t_command_table *table, char ***temp)
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