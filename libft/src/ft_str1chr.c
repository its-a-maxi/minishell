/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:17:35 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/14 09:30:22 by aleon-ca         ###   ########.fr       */
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
	i = -1;
	while (str[++i])
	{
		if (!(str[i + 1]) && (str[i] == c))
			return (str + i);
		else if (!(str[i + 1]) && (str[i] != c))
			return (0);
		else if ((i == 0) && (str[i + 1] != c) && (str[i] == c))
			return (str + i);
		else if (i == 0)
			continue;
		else if ((i != 0) && (str[i] == c) && (str[i + 1] != c)
			&& (str[i - 1] != c))
			return (str + i);
	}
	return (0);
}
