/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:17:34 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/13 20:13:37 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_errpars(t_command_table *tab, int n)
{
	write(2, EPARSE, ft_strlen(EPARSE));
	free_cmd_table(tab, n);
	return (1);	
}

int		check_redirection_error(t_command_table *tab, int *i)
{
	printf("in: %s; out: %s; app: %s;\n", tab->input_files[i[0]][0]
		, tab->output_files[i[0]][0], tab->append_files[i[0]][0]);
	if ((tab->input_files[i[0]][0])) 
	{
		if (!(tab->input_files[i[0]][0][0]))
			return (1);
	}
	else if ((tab->output_files[i[0]][0])) 
	{
		if (!(tab->output_files[i[0]][0][0]))
			return (1);
	}
	else if ((tab->append_files[i[0]][0]))
	{
		if (!(tab->append_files[i[0]][0][0]))
			return (1);
	}
	return (0);
}
