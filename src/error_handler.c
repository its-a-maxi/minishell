/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:13:17 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/13 18:35:01 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fork_error(void)
{
	write(2, "Fork error.\n", 15);
	exit_minishell();
}

void		cmd_not_found(char *str)
{
   write(2, "minishell: ", 11); 
   write(2, str, ft_strlen(str));
   write(2, " command not found.\n", 20); 
}
