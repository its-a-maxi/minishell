/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:08:21 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/07 10:13:45 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_smallest_non_zero(char **ptr)
{
	char	*smallest[1];

	if ((ptr[0]) && (ptr[1]) && (ptr[2]))
	{
		*smallest = (ptr[0] < ptr[1]) ? ptr[0] : ptr[1];
		*smallest = (*smallest < ptr[2]) ? *smallest : ptr[2];
	}
	else if (!ptr[0] && (ptr[1]) && (ptr[2]))
		*smallest = (ptr[1] < ptr[2]) ? ptr[1] : ptr[2];
	else if (!ptr[1] && (ptr[0]) && (ptr[2]))
		*smallest = (ptr[0] < ptr[2]) ? ptr[0] : ptr[2];
	else if (!ptr[2] && (ptr[0]) && (ptr[1]))
		*smallest = (ptr[0] < ptr[1]) ? ptr[0] : ptr[1];
	else if ((ptr[0]) && !ptr[1] && !ptr[2])
		*smallest = ptr[0];
	else if (!ptr[0] && (ptr[1]) && !ptr[2])
		*smallest = ptr[1];
	else if (!ptr[0] && !ptr[1] && (ptr[2]))
		*smallest = ptr[2];
	else
		*smallest = 0;
	return (*smallest);
}

static void	lone_symbol_found(t_command_table *tab, int *i, char **ptr)
{
	char	*first_ptr;
	int		len;
	char	*temp;

	first_ptr = find_smallest_non_zero(ptr);
	temp = dup_till_symbol(tab->simple_commands[i[0]][i[1] + 1]);
	len = ft_strlen(temp);
	redir_files_updt(tab, i, temp, (first_ptr == ptr[2]) * 'A'
		+ (first_ptr == ptr[0]) * 'I' + (first_ptr == ptr[1]) * 'O');
	if ((size_t)len == ft_strlen(tab->simple_commands[i[0]][i[1] + 1]))
		resize_arr_skip_pos(&tab->simple_commands[i[0]], i[1] + 1);
	else
	{
		temp = ft_strdup(tab->simple_commands[i[0]][i[1] + 1] + len);
		free(tab->simple_commands[i[0]][i[1] + 1]);
		tab->simple_commands[i[0]][i[1] + 1] = temp;
	}
	resize_arr_skip_pos(&tab->simple_commands[i[0]], i[1]);
}

static void	lone_symbol_in_word(t_command_table *tab, int *i, char *str, int t)
{
	int		len;

	free(str);
	str = dup_till_symbol(tab->simple_commands[i[0]][i[1] + 1]);
	len = ft_strlen(str);
	redir_files_updt(tab, i, str, t);
	if ((size_t)len == ft_strlen(tab->simple_commands[i[0]][i[1] + 1]))
		resize_arr_skip_pos(&tab->simple_commands[i[0]], i[1] + 1);
	else
	{
		str = ft_strdup(tab->simple_commands[i[0]][i[1] + 1] + len);
		free(tab->simple_commands[i[0]][i[1] + 1]);
		tab->simple_commands[i[0]][i[1] + 1] = str;
	}
}

static void	redirect_word_found(t_command_table *tab, int *i, char **ptr)
{
	char	*first_ptr;
	int		len;
	char	*temp;

	first_ptr = find_smallest_non_zero(ptr);
	temp = dup_till_symbol(first_ptr + 1);
	len = ft_strlen(temp);
	if (first_ptr == ptr[2])
		first_ptr[-1] = '\0';
	first_ptr[0] = '\0';
	if ((len == 0) && !(first_ptr[1]))
		lone_symbol_in_word(tab, i, temp, (first_ptr == ptr[2]) * 'A'
			+ (first_ptr == ptr[0]) * 'I' + (first_ptr == ptr[1]) * 'O');
	else
	{
		redir_files_updt(tab, i, temp, (first_ptr == ptr[2]) * 'A'
			+ (first_ptr == ptr[0]) * 'I' + (first_ptr == ptr[1]) * 'O');
		temp = ft_strdup(first_ptr + 1 + len);
		first_ptr = ft_strjoin(tab->simple_commands[i[0]][i[1]], temp);
		free(tab->simple_commands[i[0]][i[1]]);
		if (temp)
			free(temp);
		tab->simple_commands[i[0]][i[1]] = first_ptr;
		if (!(tab->simple_commands[i[0]][i[1]][0]))
			resize_arr_skip_pos(&tab->simple_commands[i[0]], i[1]);
	}
}

void		set_redirection_arr(t_command_table *tab, int *i)
{
	int		len;
	char	*str;
	char	*ptr[3];

	i[1] = -1;
	while ((str = tab->simple_commands[i[0]][++(*(i + 1))]))
	{
		if ((ft_strchr(str, '"')))
			continue;
		ptr[0] = ft_strchr(str, '<');
		ptr[1] = ft_str1chr(str, '>');
		ptr[2] = ft_str2chr(str, '>');
		if ((ptr[0]) || (ptr[1]) || (ptr[2]))
		{
			len = ft_strlen(str);
			if (((len == 1) && ((ptr[0]) || (ptr[1])))
				|| ((len == 2) && (ptr[2])))
				lone_symbol_found(tab, i, ptr);
			else
				redirect_word_found(tab, i, ptr);
			i[1] = -1;
		}
	}
}
