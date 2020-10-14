/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/14 11:42:57 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_input_subshell(char **input, char c)
{
	char		buff[1];
	int			bytes_read;
	char		*temp;

	temp = ft_strdup(ft_strchr(*input, c) + 1);
	free(*input);
	*input = temp;
	while ((bytes_read = read(0, buff, 1)) && buff[0] != c)
		*input = ft_add_char(*input, buff[0]);
	if (!bytes_read)
		write(2, "minishell: unexpected EOF while looking for matching quote\n",
			60);
	return (bytes_read);
}

void		cmd_echo(char **arg)
{
	int		i;
	char	*ptr;
	int		ret;

	i = 1;
	if (arg[i] && (arg[1][0] == '-' && arg[1][1] == 'n' && arg[1][2] == 0))
		i++;
	while (arg[i])
	{
		ret = 1;
		if ((ptr = ft_strchr(arg[i], '"')))
			ret = read_input_subshell(arg + i, *ptr);
		else if ((ptr = ft_strchr(arg[i], '\'')))
			ret = read_input_subshell(arg + i, *ptr);
		if (!ret)
			return ;
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[++i])
			write(1, " ", 1);
	}
	if (arg[1] && (arg[1][0] == '-' && arg[1][1] == 'n' && arg[1][2] == 0))
		;
	else
		write(1, "\n", 1);
}
