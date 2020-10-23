/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/23 18:23:58 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_path_error(char **arr)
{
	write(2, "\U0001F633 minishell: cd: ", 20);
	write(2, *arr, ft_strlen(*arr));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	errno = 1;
	return (1);
}

int			cmd_cd(char **arg)
{
	int		i;
	char	*path;
	char	*temp;

	if (!quotes_handler(arg, 1))
		return (0);
	if (!arg[1] || arg[1][0] == '~')
	{
		path = env_selector("HOME");
		if (!arg[1] || !arg[1][1])
			i = chdir(path);
		else
		{
			temp = ft_substr(arg[1], 1, ft_strlen(arg[1]));
			i = chdir(ft_strjoin(path, temp));
			free(temp);
		}
		free(path);
	}
	if (!quotes_handler(arg, 1))
		return (0);
	remove_quots(arg + 1);
	i = chdir(arg[1]);
	if (i != 0)
		return (cd_path_error(arg + 1));
	errno = 0;
	return (0);
}
