/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/09/23 10:58:52 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_command(char **arg)
{
	int i;

	if (!arg[1])
		chdir(env_selector("PATH"));
	if (arg[2])
	{
		write(1, "cd: string not in pwd: ", 23);
		write(1, arg[2], ft_strlen(arg[2]));
		write(1, "\n", 1);
		return (1);
	}
	if (arg[3])
	{
		write(1, "cd: too many arguments\n", 23);
		return (1);
	}
	i = chdir(arg[1]);
	if (i != 0)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, arg[1], ft_strlen(arg[1]));
		write(1, "\n", 1);
		return (1);
	}
    return (0);
}