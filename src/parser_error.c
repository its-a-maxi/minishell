/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:26:53 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 12:30:37 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_triple_ptrs(t_command_table *tab)
{
	free(tab->simple_commands);
	free(tab->input_files);
	free(tab->output_files);
	free(tab->append_files);
	free(tab->dummy_files);
}

void			free_cmd_table(t_command_table *tab, int table_num)
{
	int		i;
	int		j;

	i = -1;
	while (++i < table_num)
	{
		j = -1;
		while (++j < tab[i].simple_commands_num)
		{
			full_free((void **)tab[i].simple_commands[j],
				ft_arrlen(tab[i].simple_commands[j]));
			full_free((void **)tab[i].input_files[j],
				ft_arrlen(tab[i].input_files[j]));
			full_free((void **)tab[i].output_files[j],
				ft_arrlen(tab[i].output_files[j]));
			full_free((void **)tab[i].append_files[j],
				ft_arrlen(tab[i].append_files[j]));
			full_free((void **)tab[i].dummy_files[j],
				ft_arrlen(tab[i].dummy_files[j]));
		}
		free_triple_ptrs(tab + i);
	}
	free(tab);
}

int				free_errpars(t_command_table *tab, int n, char **lines)
{
	int		i;
	int		j;

	write(2, EPARSE, ft_strlen(EPARSE));
	full_free((void **)lines, ft_arrlen(lines));
	i = -1;
	while (++i <= n)
	{
		j = -1;
		while (++j < tab[i].simple_commands_num)
		{
			free_double(tab[i].simple_commands[j]);
			free_double(tab[i].input_files[j]);
			free_double(tab[i].output_files[j]);
			free_double(tab[i].append_files[j]);
			free_double(tab[i].dummy_files[j]);
		}
		free_triple_ptrs(tab + i);
	}
	free(tab);
	return (1);
}

int				is_parser_error(t_command_table *tab, int i)
{
	if (((tab->input_files[i][0]) && !(tab->input_files[i][0][0]))
		|| ((tab->output_files[i][0])
			&& !(tab->output_files[i][0][0]))
		|| ((tab->append_files[i][0])
			&& !(tab->append_files[i][0][0])))
		return (1);
	else
		return (0);
}
