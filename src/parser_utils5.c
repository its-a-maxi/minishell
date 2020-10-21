/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:07:54 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 12:24:16 by aleon-ca         ###   ########.fr       */
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
			break ;
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
			&& ((is_inside_jth_quote_pair(quotpos, str + i) != -1)
			|| ((size % 2) && (str + i > quotpos[size - 1]))))
			continue ;
		else if (str[i] == c)
			count++;
	}
	return (count);
}

char		*ft_strchr__quots(char **quotpos, char *str, char c)
{
	int		i;
	int		size;

	if (!str)
		return (0);
	if (!quotpos[0])
		return (ft_strchr(str, c));
	size = ft_arrlen(quotpos);
	i = -1;
	while (str[++i])
	{
		if ((str[i] == c)
			&& ((is_inside_jth_quote_pair(quotpos, str + i) != -1)
			|| ((size % 2) && (str + i > quotpos[size - 1]))))
			continue ;
		else if (str[i] == c)
			return (str + i);
	}
	return (0);
}

char		*ft_str2chr__quots(char **quotpos, char *str, char c)
{
	int		i;
	int		size;

	size = ft_arrlen(quotpos);
	i = -1;
	while ((str[++i]) && (str[i + 1]))
	{
		if ((str[i] == c) && (str[i + 1] == c)
			&& ((is_inside_jth_quote_pair(quotpos, str + i) != -1)
			|| ((size % 2) && (str + i > quotpos[size - 1]))))
			continue ;
		else if ((str[i] == c) && (str[i + 1] == c))
			return (str + i + 1);
	}
	return (0);
}

char		*ft_str1chr__quots(char **quotpos, char *str, char c)
{
	int		i;
	int		size;

	size = ft_arrlen(quotpos);
	i = -1;
	while (str[++i])
	{
		if ((is_inside_jth_quote_pair(quotpos, str + i) != -1)
			|| ((size % 2) && (str + i > quotpos[size - 1])))
			continue;
		else if (!(str[i + 1]) && (str[i] == c) && (i) && (str[i - 1] != c))
			return (str + i);
		else if (!(str[i + 1]) && (i) && ((str[i] != c)
			|| (str[i - 1] == c)))
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
