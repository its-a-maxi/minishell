/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:05:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/18 18:03:00 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Like ft_split but it considers a quoted sentence as a
** whole "character" when splitting, v. g.,
**	ft_split__quots("echo '"'Oye chico!'"'");
**	returns arr[] = {echo, "Oye chico!", NULL}
** the '"' or '\'' stay to signal the redirection parser not to consider
** any redirection in that string.
*/

static char	*smallest_non_zero(char *ptr1, char *ptr2)
{
	if (!ptr1 && !ptr2)
		return (NULL);
	else if (!ptr1)
		return (ptr2);
	else if (!ptr2)
		return (ptr1);
	else
		return ((ptr1 < ptr2) ? ptr1 : ptr2);
}

static char	**set_quotpos_arr(char *str)
{
	char	*ptr;
	char	**quotpos;
	int		count;

	count = 0;
	quotpos = malloc(sizeof(char *) * 1);
	*quotpos = NULL;
	while ((ptr = smallest_non_zero(ft_strchr(str, '"'), ft_strchr(str, '\''))))
	{
		if ((str = ft_strchr(ptr + 1, *ptr)))
		{
			ft_add_str(&quotpos, ptr);
			ft_add_str(&quotpos, str);
			ptr = str + 1;
		}
		else
		{
			ft_add_str(&quotpos, ptr);
			break;
		}
	}
	return (quotpos);
}

static void	loop_table(char **tab, char *str, char c, char **quotpos)
{
	int		i;
	int		j;
	char	*pos;

	j = 0;
	i = -1;
	while ((pos = ft_strchr(str, c)))
	{
		if (!((pos > quotpos[j]) && (pos < quotpos[j + 1])))
		{
			*pos = '\0';
			tab[++i] = ft_strdup(str);
			str = pos + 1;
		}
		else
		{
			*quotpos[j + 1] = '\0';
			tab[++i] = ft_strdup(quotpos[j]);
			str = quotpos[j + 1] + 1;
			tab[i] = ft_add_char(tab[i], *quotpos[j]);
			j += 2;
			while ((*str) && (*str == c))
				str++;
		}
	}
	if ((str > quotpos[j + 1]) && (*str))
		tab[++i] = ft_strdup(str);
	else if ((*str))
		tab[++i] = ft_strdup(quotpos[j]);
}

char		**ft_split__quots(char *str, char c)
{
	char	**quotpos;
	char	**table;
	char	temp;
	int		count;
	int		i;

	quotpos = set_quotpos_arr(str);
	count = 0;
	i = -1;
	while (quotpos[++i])
	{
		temp = *quotpos[i];
		*quotpos[i] = '\0';
		count += ft_strnchr(str, c);
		if ((quotpos[i + 1]))
			str = quotpos[i + 1] + 1;
		*quotpos[i] = temp;
	}
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
	if (ft_arrlen(quotpos) > 1)
		loop_table(table, str, c, quotpos);
	else
	return (table);
}
