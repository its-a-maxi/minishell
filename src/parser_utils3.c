/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:25:34 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 13:18:17 by aleon-ca         ###   ########.fr       */
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

static void	errno_updt(char **strdir)
{
	free(*strdir);
	*strdir = ft_itoa(errno);
}

static void	inside_str_updt(char *ptr, char *str, char **strdir)
{
	char	*temp;
	char	*temp2;

	ptr[-1] = '\0';
	temp = ft_strdup(*strdir);
	temp2 = ft_strjoin(temp, str);
	free(temp);
	temp = ft_strjoin(temp2, ptr + ft_strlen(str));
	free(str);
	free(temp2);
	free(*strdir);
	*strdir = temp;
	if ((temp = smallest_non_zero(ft_strchr(*strdir, '"'),
		ft_strchr(*strdir, '\''))))
		*strdir = ft_add_char(*strdir, *temp);
}

static void	replace_var_in_str(char **strdir, char *ptr)
{
	char	*str;
	char	*temp;

	if (*ptr == '?')
		errno_updt(strdir);
	if ((temp = smallest_non_zero(ft_strchr(*strdir, '"'),
		ft_strchr(*strdir, '\''))))
		*(ft_strchr(temp + 1, *temp)) = '\0';
	if (ft_strlen((str = env_selector(ptr))) == ft_strlen(*strdir))
	{
		free(*strdir);
		*strdir = str;
	}
	else
		inside_str_updt(ptr, str, strdir);
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
