/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:13:17 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 12:27:58 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		fork_error(void)
{
	write(2, "\U0001F633 Fork error.\n", 20);
	exit_minishell();
}

void		cmd_not_found(char *str)
{
	write(2, "\U0001F633 minishell: ", 16);
	write(2, str, ft_strlen(str));
	write(2, " command not found.\n", 20);
}
