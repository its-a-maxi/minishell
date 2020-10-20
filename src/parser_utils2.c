/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:05:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/19 19:07:33 by aleon-ca         ###   ########.fr       */
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

static int	no_char_between_quotes(char **quotpos, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while ((quotpos[i]) && (quotpos[i + 1]))
	{
		*quotpos[i + 1] = '\0';
		ptr = ft_strchr(quotpos[i], c);
		*quotpos[i + 1] = *quotpos[i];
		if ((ptr))
			return (0);
		else
			i += 2;
	}
	return (1);
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
//Cambiar condiciones a
//Estar a la dcha de la comilla aislada
//Estar entre una pareja de comillas
//Cualquier otro caso
		if (!(quotpos[j + 1]) && (pos > quotpos[j]))
		{
			tab[++i] = ft_strdup(str);
			str += ft_strlen(str);
		}
		else if ((!((pos > quotpos[j]) && (pos < quotpos[j + 1]))))
		{
			*pos = '\0';
			tab[++i] = ft_strdup(str);
			str = pos + 1;
		}	
		else
		{
			*quotpos[j + 1] = '\0';
			tab[++i] = ft_strdup(smallest_non_zero(str, quotpos[j]));
			str = quotpos[j + 1] + 1;
			tab[i] = ft_add_char(tab[i], *quotpos[j]);
			j += 1;
			while ((*str) && ((*str == ' ') || (*str == c)))
				str++;
		}
	}
	if ((*str) && !(quotpos[j + 1]))
		tab[++i] = ft_strdup(str);
	else if ((*str) && (str > quotpos[j + 1]))
		tab[++i] = ft_strdup(str);
	else if ((*str))
		tab[++i] = ft_strdup(quotpos[j]);
}

char		**ft_split__quots(char *str, char c)
{
	char	**quotpos;
	char	**table;
	int		count;

	quotpos = set_quotpos_arr(str);
	if (!(quotpos[0]) || (no_char_between_quotes(quotpos, c)))
	{
		free(quotpos);
		return (ft_split(str, c));
	}
	count = count_not_quoted_char(quotpos, str, c);
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
	loop_table(table, str, c, quotpos);
	remove_dummy_quots(table);
	free(quotpos);
	return (table);
}
