/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:26:03 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/19 10:57:30 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((ptr = smallest_non_zero(ft_strchr(arg[i], '"'),
			ft_strchr(arg[i], '\''))) && !(ft_strchr(ptr + 1, *ptr)))
			ret = read_input_subshell(arg + i, *ptr, ptr);
		else
			remove_quots(arg + i);
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
