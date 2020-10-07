/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/07 12:03:23 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_cd(char **arg)
{
	int i;
	char *path;

	if (!arg[1] || arg[1] == '~')
	{
		path = env_selector("HOME");
		chdir(path);
		free(path);
		return (0);
	}
	if (arg[2] && !arg[3])
	{
		write(1, "cd: string not in pwd: ", 23);
		write(1, arg[1], ft_strlen(arg[1]));
		write(1, "\n", 1);
		return (1);
	}
	if (arg[2] && arg[3])
	{
		write(1, "cd: too many arguments\n", 23);
		return (1);
	}
	i = chdir(arg[1]);
	if (i != 0)
	{
		write(1, "cd: ", 4);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", 2);
		write(1, arg[1], ft_strlen(arg[1]));
		write(1, "\n", 1);
		return (1);
	}
    return (0);
}