/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:05:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 11:02:20 by aleon-ca         ###   ########.fr       */
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

static int	are_char_between_quotes(char **quotpos, char c)
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
			return (1);
		else
			i += 2;
	}
	return (0);
}

int			is_inside_jth_quote_pair(char **quotpos, char *pos)
{
	int		j;

	j = 0;
	while ((quotpos[j]) && (quotpos[j + 1]))
	{
		if ((pos > quotpos[j]) && (pos < quotpos[j + 1]))
			return (j);
		else
			j += 2;
	}
	return (-1);
}

static void	loop_table(char **tab, char *str, char c, char **quotpos)
{
	int		i;
	int		size;
	char	*pos;

	size = ft_arrlen(quotpos);
	i = -1;
	while ((pos = ft_strchr__quots(quotpos, str, c)))
	{
//ft_printf("pos: ->%s<-\n", pos);
		*pos = '\0';
		tab[++i] = ft_strdup(str);
		str = pos + 1;
//ft_printf("str: ->%s<-\n", str);
//ft_printf("Saved tab [%d]: ->%s<-\n", i, tab[i]);
	}
	if ((*str))
		tab[++i] = ft_strdup(str);
	else
		tab[++i] = NULL;
//ft_printf("Saved tab [%d]: ->%s<-\n", i, tab[i]);
}

char		**ft_split__quots(char *str, char c)
{
	char	**quotpos;
	char	**table;
	int		count;

	quotpos = set_quotpos_arr(str);
	if (!(quotpos[0]) || !(are_char_between_quotes(quotpos, c)))
	{
		free(quotpos);
		return (ft_split(str, c));
	}
	count = count_not_quoted_char(quotpos, str, c);
ft_printf("\tcount: %d\n", count);
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
//printf("Entering loop table...\n");
	loop_table(table, str, c, quotpos);
	remove_dummy_quots(table);
//printf("Removed dummy quotes.\n");
	free(quotpos);
	return (table);
}
