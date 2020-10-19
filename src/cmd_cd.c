/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:09:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/17 12:46:10 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_input_subshell(char **input, char c, char *ptr)
{
	char	buff[1];
	int		bytes_read;
	char	*temp;

	*ptr = '\0';
	temp = ft_strjoin(*input, ptr + 1);
	free(*input);
	*input = temp;
	while ((bytes_read = read(0, buff, 1)) && buff[0] != c)
		*input = ft_add_char(*input, buff[0]);
	if (!bytes_read)
		write(2, "minishell: unexpected EOF while looking for matching quote\n",
			60);
	return (bytes_read);
}

static int	cd_path_error(char **arr)
{
	write(2, "minishell: cd: ", 15);
	write(2, *arg, ft_strlen(*arg));
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
	if ((ptr = ft_strchr(arg[1], '"')))
		ret = read_input_subshell(arg + 1, *ptr, ptr);
	if (!ret)
		return ;
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
