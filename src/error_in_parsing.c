/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_in_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:05:22 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/01 13:06:35 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int		free_error_parsing(t_command_table *tab, int n)
//{
//	free_command_tables(tab, n);
//	return (1);	
//}

void		check_redirection_error(char *str)
{
	if ((!(ft_strcmp(str, ">")) || !(ft_strcmp(str, "<"))
		|| !(ft_strcmp(str, ">>"))))
	{
		ft_printf("%s", EREDIR);
		exit_minishell();
	}
}
