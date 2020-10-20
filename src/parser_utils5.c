/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:07:54 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/20 12:50:18 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**set_quotpos_arr(char *str)
{
	char	*ptr;
	char	**quotpos;

	quotpos = malloc(sizeof(char *) * 1);
	*quotpos = NULL;
	while ((ptr = smallest_non_zero(ft_strchr(str, '"'), ft_strchr(str, '\''))))
	{
		if ((str = ft_strchr(ptr + 1, *ptr)))
		{
			ft_add_str(&quotpos, ptr);
			ft_add_str(&quotpos, str);
			str++;
		}
		else
		{
			ft_add_str(&quotpos, ptr);
			break;
		}
	}
	return (quotpos);
}

int			count_not_quoted_char(char **quotpos, char *str, char c)
{
	int		i;
	int		count;
	int		size;

	size = ft_arrlen(quotpos);
	count = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == c)
		&& ((!(size % 2) && (is_inside_jth_quote_pair(quotpos, str + i) == -1))
			|| ((size % 2) && ((str + i) < quotpos[ft_arrlen(quotpos) - 1]))))
			count++;
	}
	return (count);
}
