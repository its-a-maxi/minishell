/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:03:39 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/13 13:49:57 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		advance_ptr_eof(int fd)
{
	//Avanzar fd pointer hasta el final del archivo
	char	buff[1];
	int		ret;

	while ((ret = read(fd, buff, 1)) > 0)
		;
	if (ret < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(1);
	}
}

void		overwrite_ptr_begin(int fd)
{
	//Borrar contenido del archivo y poner el fd pointer al ppo.
	char	buff;

	buff = 4;
	write(fd, &buff, 1);
	close(fd);
}
