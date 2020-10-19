/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/19 09:47:11 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_path_error(char **arr)
{
	write(2, "minishell: cd: ", 15);
	write(2, *arr, ft_strlen(*arr));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (1);
}

int			cmd_cd(char **arg)
{
	int		i;
	char	*path;
	char	*ptr;
	int		ret;

	ret = 1;
	if ((ptr = smallest_non_zero(ft_strchr(arg[1], '"'),
		ft_strchr(arg[1], '\''))) && !(ft_strchr(ptr + 1, *ptr)))
		ret = read_input_subshell(arg + 1, *ptr, ptr);
	else
		remove_quots(arg + 1);
	if (!ret)
		return (0);
	if (!arg[1] || arg[1][0] == '~')
	{
		path = env_selector("HOME");
		chdir(path);
		free(path);
		return (0);
	}
	i = chdir(arg[1]);
	if (i != 0)
		return (cd_path_error(arg + 1));
	return (0);
}
