/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:47:17 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 12:02:21 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split(const char *s, char c)
{
	char	*str;
	char	*pos;
	int		count;
	char	**table;

	str = (char *)s;
	count = ft_strnchr(str, c);
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
	count = -1;
	while ((pos = ft_strchr(str, c)))
	{
		*pos = '\0';
		table[++count] = ft_strdup(str);
		str = pos + 1;
	}
	table[++count] = ft_strdup(str);
	return (table);
}
