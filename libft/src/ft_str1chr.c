/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:17:35 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/06 17:15:49 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str1chr(char *str, char c)
{
	int		i;

	if (!str)
		return (0);	
	i = -1;
	while (str[++i] && str[i + 1])
	{
		if ((str[i] == c) && (str[i + 1] != c)
			&& (ft_strchr(str, c) == str + i))
			return (str + i);
	}
	return (0);
}
