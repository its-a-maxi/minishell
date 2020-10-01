/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:03:05 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/01 13:14:40 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_backslash(char **strdir, char *slashpos)
{
	char	*str;
	char	*temp;

	if ((ft_strlen(str = ft_strdup(slashpos + 1))) == ft_strlen(*strdir))
	{
		free(*strdir);
		*strdir = str;
	}
	else
	{
		*slashpos = '\0';
		temp = ft_strjoin(*strdir, str);
		free(*strdir);
		free(str);
		*strdir = temp;
	}
}

static void	replace_var_in_str(char **strdir, char *ptr)
{
	char	*str;
	char	*temp;
	char	*temp2;

	if (ft_strlen((str = env_selector(ptr))) == ft_strlen(*strdir))
	{
		free(*strdir);
		*strdir = str;
	}
	else
	{
		ptr[-1] = '\0';
		temp = ft_strdup(*strdir);
		temp2 = ft_strjoin(temp, str);
		free(temp);
		temp = ft_strjoin(temp2, ptr + ft_strlen(str));
		free(str);
		free(temp2);
		free(*strdir);
		*strdir = temp;
	}
}

void		replace_env_var(t_command_table *table)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	while (table->simple_commands[++i])
	{
		j = -1;
		while (table->simple_commands[i][++j])
		{
			if ((ptr = ft_strchr(table->simple_commands[i][j], '$')))
			{
				if (((ptr - table->simple_commands[i][j]) != 0)
					&& (ptr[-1] == '\\'))
					remove_backslash(&table->simple_commands[i][j], ptr - 1);
				else
					replace_var_in_str(&table->simple_commands[i][j], ptr + 1);
			}
		}
	}
}

void		initr(t_command_table *tab, int i, int *count)
{
	i = 0;
	tab->input_file/*[i]*/ = NULL;
	count[0] = 0;
	tab->output_file/*[i]*/ = NULL;
	count[1] = 0;
	tab->append_file/*[i]*/ = NULL;
	count[2] = 0;
}

void		arr_swap(char ***new, char ***old)
{
	full_free((void **)*old, ft_arrlen(*old));
	*old = *new;
}
