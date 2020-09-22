/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:47:17 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/22 13:36:49 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**init_table(char *str, int c)
{
	int		i;
	char	**table;

	i = ft_strnchr(str, c);
	table = malloc(sizeof(char *) * (i + 1));
	table[i] = NULL;
	return (table);
}

static char	**loop_table(char **table, char *str, int c)
{
	int		i;
	char	*pos;

	i = -1;
	while ((pos = ft_strchr(str, c)))
	{
		*pos = '\0';
		table[++i] = ft_strdup(str);
		str = pos + 1;
	}
	table[++i] = ft_strdup(str);
	return (table);
}

char		**ft_split(const char *s, char c)
{
	char	*str;
	char	*pos;
	char	*temp;
	char	**table;

	str = (char *)s;
	if (!(pos = ft_strchr(str, c)))
	{
		table = malloc(sizeof(char *) * 2);
		table[0] = ft_strdup(str);
		table[1] = NULL;
		return (table);
	}
	else
	{
		temp = str;
		table = init_table(str, c);
		table = loop_table(table, str, c);
		str = temp;
		return (table);
	}
}
