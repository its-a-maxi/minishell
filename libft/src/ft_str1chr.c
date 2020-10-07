/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:17:35 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/07 10:03:37 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Encontrar un char c aislado, sin copias suyas de vecinos.
*/
char		*ft_str1chr(char *str, char c)
{
	int		i;

	if (!str)
		return (0);
	if ((int)ft_strlen(str) == 1)
		return (ft_strchr(str, c));
	else if ((int)ft_strlen(str) == 2)
	{
		if ((str[0] == c) && (str[1] != c))
			return (str);
		else if ((str[0] != c) && (str[1] == c))
			return (str + 1);
		else
			return (0);
	}
	i = -1;
	while (str[++i] && str[i + 1])
	{
		if ((i == 0) && (str[i] == c) && (str[i + 1] != c))
			return (str + i);
		else if ((str[i] == c) && (str[i + 1] != c) && (str[i - 1] != c))
			return (str + i);
	}
	return (0);
}
