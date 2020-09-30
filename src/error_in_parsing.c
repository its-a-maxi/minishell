/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_in_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 10:05:22 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/30 10:16:06 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirection_error(char *str)
{
	if (((ft_strcmp(str, ">")) || (ft_strcmp(str, "<"))
		|| (ft_strcmp(str, ">>"))))
	{
		ft_printf("%s", EREDIR);
		exit_minishell();
	}
}
