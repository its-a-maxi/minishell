/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/13 11:07:42 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	two_arg_error(char **arg)
{
	if (arg[2] && !arg[3])
	{
		write(2, "cd: string not in pwd: ", 23);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

static int	misc_errors(int i, char **arg)
{
	if (i != 0)
	{
		write(2, "cd: ", 4);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

int			cmd_cd(char **arg)
{
	int		i;
	char	*path;

printf("ESTOY EN CASA\n");
	if (!arg[1] || arg[1][0] == '~')
	{
		path = env_selector("HOME");
		chdir(path);
		free(path);
		return (0);
	}
	if (two_arg_error(arg))
		return (1);
	if (arg[2] && arg[3])
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	i = chdir(arg[1]);
	if (misc_errors(i, arg))
		return (1);
	return (0);
}
