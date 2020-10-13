/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/13 11:43:25 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(char **arg)
{
	int i;

	i = 1;
	if (arg[i] && (arg[1][0] == '-' && arg[1][1] == 'n' && arg[1][2] == 0))
		i++;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[++i])
			write(1, " ", 1);
	}
	if (arg[1] && (arg[1][0] == '-' && arg[1][1] == 'n' && arg[1][2] == 0))
	{
		if (!arg[2])
			return ;
	}
	else
		write(1, "\n", 1);
	exit(0);
	return ;
}
