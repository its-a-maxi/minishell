/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 13:19:28 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/19 12:52:34 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(char **arg)
{
	char	buff[4096 + 1];

	buff[4096] = '\0';
	(void)arg;
	getcwd(buff, 4096);
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
	errno = 0;
	return ;
}
