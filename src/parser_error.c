/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:17:34 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/06 16:21:28 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_errpars(t_command_table *tab, int n)
{
	free_cmd_table(tab, n);
	return (1);	
}

int		check_redirection_error(t_command_table *tab, int *i)
{
	if ((tab->input_files[i[0]][0])) 
	{
		if (!(tab->input_files[i[0]][0][0]))
		{
			ft_printf("%s", EREDIR);
			return (1);
		}
	}
	else if ((tab->output_files[i[0]][0])) 
	{
		if (!(tab->output_files[i[0]][0][0]))
		{
			ft_printf("%s", EREDIR);
			return (1);
		}
	}
	else if ((tab->append_files[i[0]][0]))
	{
		if (!(tab->append_files[i[0]][0][0]))
		{
			ft_printf("%s", EREDIR);
			return (1);
		}
	}
	return (0);
}
