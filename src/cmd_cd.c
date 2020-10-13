/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/13 12:07:28 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_cd(char **arg)
{
	int		i;
	char	*path;

	if (!arg[1] || arg[1][0] == '~')
	{
		path = env_selector("HOME");
		chdir(path);
		free(path);
		return (0);
	}
	i = chdir(arg[1]);
	if (i != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}
