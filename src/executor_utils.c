/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:30:19 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/13 13:43:51 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_start_executable_path(char *str)
{
	if (ft_strlen(str) <= 2)
		return (0);
	if (str[0] == '.')
	{
		if ((str[1] == '.') && (str[2] == '/'))
			return (1);
		else if (str[1] == '/')
			return (1);
		else
			return (0);
	}
	else if ((str[0] == '~') && (str[1] == '/'))
		return (1);
	return (0);
}

int		is_built_in(char **arr)
{
	if (!(ft_strcmp(arr[0], "echo")))
		return (1);
	else if (!(ft_strcmp(arr[0], "cd")))
		return (1);
	else if (!(ft_strcmp(arr[0], "pwd")))
		return (1);
	else if (!(ft_strcmp(arr[0], "export")))
		return (1);
	else if (!(ft_strcmp(arr[0], "unset")))
		return (1);
	else if (!(ft_strcmp(arr[0], "env")))
		return (1);
	else if (!(ft_strcmp(arr[0], "exit")))
		return (1);
	else
		return (0);
}

void	choose_and_execute(char **arr)
{
	if (!(ft_strcmp(arr[0], "echo")))
		cmd_echo(arr);
	else if (!(ft_strcmp(arr[0], "cd")))
		cmd_cd(arr);
	else if (!(ft_strcmp(arr[0], "pwd")))
		cmd_pwd(arr);
	else if (!(ft_strcmp(arr[0], "export")))
		cmd_export(arr);
	else if (!(ft_strcmp(arr[0], "unset")))
		cmd_unset(arr);
	else if (!(ft_strcmp(arr[0], "env")))
		cmd_env(arr);
	else if (!(ft_strcmp(arr[0], "exit")))
		cmd_exit();
}

int		is_cmd_cd(char **arr, int simple_commands_num)
{
	if (!(ft_strcmp(arr[0], "cd")) && !((ft_arrlen(arr) == 1)
		&& (simple_commands_num != 1)))
	{
		cmd_cd(arr);
		return (1);
	}
	else if (!(ft_strcmp(arr[0], "cd")))
		return (1);
	else
		return (0);
}
int		fork_and_check_error(void)
{
	int		ret;

	if ((ret = fork()) < 0)
		fork_error();
	else if (ret == 0)
		return (0);
	else
		return (1);
	return (1);
}
