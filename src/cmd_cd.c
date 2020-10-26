/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/26 13:15:12 by aleon-ca         ###   ########.fr       */
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

static void	replace_home_dir(char **strdir)
{
	char	*temp[2];

	temp[0] = env_selector("HOME");
	temp[1] = ft_strjoin(temp[0], *strdir + 1);
	free(temp[0]);
	free(*strdir);
	*strdir = temp[1];
}

int			cmd_cd(char **arg)
{
	int		i;
	char	*path;
	
	if (!quotes_handler(arg, 1))
		return (0);
	if (!arg[1])
	{
		path = env_selector("HOME");
		i = chdir(path);
		free(path);
		if (i != 0)
			return (cd_path_error(arg + 1));
		errno = 0;
		return (0);
	}
	if (arg[1][0] == '~')
		replace_home_dir(arg + 1);
	remove_quots(arg + 1);
	i = chdir(arg[1]);
	if (i != 0)
		return (cd_path_error(arg + 1));
	errno = 0;
	return (0);
}
