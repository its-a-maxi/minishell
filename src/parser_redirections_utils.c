/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:09:42 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/07 10:14:18 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dummy_update(t_command_table *tab, int *i, char *str, int type)
{
	int		j;
	char	**temp;

	temp = malloc(sizeof(char *) * (ft_arrlen(tab->dummy_files[i[0]]) + 2));
	temp[ft_arrlen(tab->dummy_files[i[0]]) + 1] = NULL;
	j = -1;
	while ((tab->dummy_files[i[0]][++j]))
		temp[j] = ft_strdup(tab->dummy_files[i[0]][j]);
	if ((tab->output_files[i[0]][0]))
	{
		temp[j] = ft_strdup(tab->output_files[i[0]][0]);
		free(tab->output_files[i[0]][0]);
		tab->output_files[i[0]][0] = NULL;
	}
	if ((tab->append_files[i[0]][0]))
	{
		temp[j] = ft_strdup(tab->append_files[i[0]][0]);
		free(tab->append_files[i[0]][0]);
		tab->append_files[i[0]][0] = NULL;
	}
	if (type == 'O')
		tab->output_files[i[0]][0] = ft_strdup(str);
	if (type == 'A')
		tab->append_files[i[0]][0] = ft_strdup(str);
	full_free((void **)tab->dummy_files[i[0]],
		ft_arrlen(tab->dummy_files[i[0]]));
	tab->dummy_files[i[0]] = temp;
}

void		redir_files_updt(t_command_table *tab, int *i, char *str, int type)
{
	if ((type == 'A') && (!(tab->output_files[i[0]][0])
		&& !(tab->append_files[i[0]][0])))
		tab->append_files[i[0]][0] = ft_strdup(str);
	else if ((type == 'O') && (!(tab->output_files[i[0]][0])
		&& !(tab->append_files[i[0]][0])))
		tab->output_files[i[0]][0] = ft_strdup(str);
	else if (((type == 'O') || (type == 'A')) && ((tab->output_files[i[0]][0])
		|| (tab->append_files[i[0]][0])))
		dummy_update(tab, i, str, type);
	else if ((type == 'I') && !(tab->input_files[i[0]][0]))
		tab->input_files[i[0]][0] = ft_strdup(str);
	else if ((type == 'I') && ((tab->input_files[i[0]][0])))
	{
		free(tab->input_files[i[0]][0]);
		tab->input_files[i[0]][0] = ft_strdup(str);
	}
	free(str);
}

void		count_redirections(char **arr, int *count)
{
	int		i;
	char	*ptr[2];

	i = -1;
	while (arr[++i])
	{
		if ((ft_strchr(arr[i], '"')))
			continue;
		ptr[1] = arr[i];
		while ((ptr[0] = ft_strchr(ptr[1], '<'))
			&& (ptr[1] = ptr[0] + 1))
			count[0]++;
		ptr[1] = arr[i];
		while ((ptr[0] = ft_strchr(ptr[1], '>')) && (ptr[0][1] != '>')
				&& (ptr[1] = ptr[0] + 1))
			count[1]++;
		ptr[1] = arr[i];
		while ((ptr[0] = ft_str2chr(ptr[1], '>'))
				&& (ptr[1] = ptr[0] + 1))
			count[2]++;
	}
}

void		init_redirection_arr(t_command_table *tab, int *i, int *count)
{
	tab->input_files[i[0]] = malloc(sizeof(char *) * ((count[0] > 0) + 1));
	tab->input_files[i[0]][(count[0] > 0)] = NULL;
	if (count[0] > 0)
		tab->input_files[i[0]][0] = NULL;
	tab->output_files[i[0]] = malloc(sizeof(char *) * ((count[1] > 0) + 1));
	tab->output_files[i[0]][(count[1] > 0)] = NULL;
	if (count[1] > 0)
		tab->output_files[i[0]][0] = NULL;
	tab->append_files[i[0]] = malloc(sizeof(char *) * ((count[2] > 0) + 1));
	tab->append_files[i[0]][(count[2] > 0)] = NULL;
	if (count[2] > 0)
		tab->append_files[i[0]][0] = NULL;
	tab->dummy_files[i[0]] = malloc(sizeof(char *) * 1);
	tab->dummy_files[i[0]][0] = NULL;
}

char		*dup_till_symbol(char *str)
{
	int		i;
	char	*result;

	if (!str)
		return (0);
	i = -1;
	while (str[++i] && (str[i] != '>') && (str[i] != '<'))
		;
	if (!(result = malloc(sizeof(char) * (i + 1))))
		return (0);
	result[i] = '\0';
	i = -1;
	while (str[++i] && (str[i] != '>') && (str[i] != '<'))
		result[i] = str[i];
	return (result);
}
