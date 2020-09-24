/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 13:19:28 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/09/24 12:28:47 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cmd_pwd(char **arg)
{
    char    buff[4096 + 1];
    
    buff[4096] = '\0';
    if (!arg[1])
	{
        getcwd(buff, 4096);
	    write(1, buff, strlen(buff));
    }
    else
        write (1, "pwd: too many arguments", 23);
    write(1, "\n", 1);
    return;
}