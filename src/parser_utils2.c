/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:05:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/28 11:24:13 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Removes the possible empty strings after a ft_split call. Also removes
** the '"' from possible remaining '"'-encapsulated sentences.
**
** returns:		the array of strings resulted from the split call, minus the
**				empty ones, or any remaining '"'-encapsulated sentences.
**
** parameter #1:	an array of strings
*/

static void	remove_quots(char **arr)
{
	int		i;
	char	*quotpos;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		while ((quotpos = ft_strchr(arr[i], '"')))
		{
			*quotpos = '\0';
			temp = ft_strjoin(arr[i], quotpos + 1);
			free(arr[i]);
			arr[i] = temp;
		}
	}
//printf("\tremove quots successful\n");
}

char		**remove_empty_str(char **arr)
{
	int		i;
	int		count;
	char	**result;

	count = 0;
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] != '\0')
			count++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	result[count] = NULL;
	count = -1;
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] != '\0')
			result[++count] = ft_strdup(arr[i]);
	}
	full_free((void **)arr, ft_arrlen(arr));
	remove_quots(result);
	arr = result;
//printf("\tremove empty strings successful\n");
	return (arr);
}

/*
** Like ft_split but it considers a '"'-encapsulated sentence as a
** whole "character" when splitting, v. g.,
**	ft_split_and_quotations("echo '"'Oye chico!'"'");
**	returns arr[] = {echo, Oye chico!, NULL}
*/

static void	loop_table(char **tab, char *str, char c, char **quotpos)
{
	int		i;
	char	*pos;

	i = -1;
	while ((pos = ft_strchr(str, c)))
	{
		if (!((pos > quotpos[0]) && (pos < quotpos[1])))
		{
			*pos = '\0';
			tab[++i] = ft_strdup(str);
			str = pos + 1;
//int j = -1; printf("one loop set:");while (tab[i][++j]){printf("%c", tab[i][j]);}printf("\n");
		}
		else
		{
			*(*(quotpos + 1)) = '\0';
			tab[++i] = ft_strdup(quotpos[0] + 1);
			str = quotpos[1] + 1;
			while ((*str) && (*str == c))
				str++;
//int j = -1; printf("one loop set:");while (tab[i][++j]){printf("%c", tab[i][j]);}printf("\n");
		}
	}
	if ((str > quotpos[1]) && (*str))
		tab[++i] = ft_strdup(str);
	else if ((*str))
		tab[++i] = ft_strdup(quotpos[0] + 1);
//printf("last loop set:%s\n", tab[i]);
}

char		**ft_split_and_quotations(char *str, char c)
{
	char	*quotpos[2];
	char	**table;
	int		count;

	quotpos[0] = ft_strchr(str, '"');
	if ((quotpos[0]))
		quotpos[1] = ft_strchr(quotpos[0] + 1, '"');
	if (!(ft_strchr(str, c)) || !(quotpos[0]) || !(quotpos[1])
		|| ((ft_strchr(str, c)) > quotpos[1]))
		return (ft_split(str, c));
	*(*(quotpos + 1)) = '\0';
	*(*quotpos) = '\0';
	count = ft_strnchr(str, c);
	count += ft_strnchr(quotpos[1] + 1, c);
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
//printf("Table size:%d\n", count + 1);
	*(*(quotpos + 1)) = '"';
	*(*quotpos) = '"';
	loop_table(table, str, c, quotpos);
	int i = -1;while (table[++i]){printf("\ttable[%d]:%s\n", i, table[i]);}
//printf("printing ended\n");
	return (table);
}
