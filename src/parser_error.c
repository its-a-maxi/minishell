/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:17:34 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/01 17:29:55 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_errpars(t_command_table *tab, int n)
{
	freetb(tab, n);
	return (1);	
}

int		check_redirection_error(char *str)
{
	if ((!(ft_strcmp(str, ">")) || !(ft_strcmp(str, "<"))
		|| !(ft_strcmp(str, ">>"))))
	{
		ft_printf("%s", EREDIR);
		return (1);
	}
	return (0);
}
