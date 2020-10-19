/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:39:56 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/19 12:37:25 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(char **arg)
{
	int	i;

	i = -1;
	if (arg[1])
	{
		write(2, "env: ", 5);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": No such file or directory\n", 28);
		errno = 127;
		return ;
	}
	while (g_env[++i])
	{
		write(1, g_env[i], ft_strlen(g_env[i]));
		write(1, "\n", 1);
	}
	errno = 0;
	return ;
}
