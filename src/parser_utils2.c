/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:05:18 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/06 17:30:50 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		resize_arr_skip_pos(char ***arr, int pos)
{
	int		i;
	int		j;
	int		arr_size;
	char	**temp;

	arr_size = ft_arrlen(*arr);
	temp = malloc(sizeof(char *) * (arr_size));
	temp[arr_size - 1] = NULL;
	i = -1;
	j = -1;
	while (*((*arr) + ++i))
	{
		if (i == pos)
			continue;
		else
			temp[++j] = ft_strdup(*((*arr) + i));
	}
	full_free((void **)*arr, arr_size);
	*arr = temp;
}

/*
** Removes the possible empty strings after a ft_split call. Also removes
** the '"' from possible remaining '"'-encapsulated sentences.
**
** returns:		the array of strings resulted from the split call, minus the
**				empty ones, or any remaining '"'-encapsulated sentences.
**
** parameter #1:	an array of strings
*/

void		remove_quots(char ***arr)
{
	int		i;
	char	*quotpos;
	char	*temp;

	i = -1;
	while (*(*arr + ++i))
	{
		while ((quotpos = ft_strchr(*(*arr + i), '"')))
		{
			*quotpos = '\0';
			temp = ft_strjoin(*(*arr + i), quotpos + 1);
			free(*(*arr + i));
			*(*arr + i) = temp;
		}
	}
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
	arr = result;
	return (arr);
}

/*
** Like ft_split but it considers a '"'-encapsulated sentence as a
** whole "character" when splitting, v. g.,
**	ft_split__quots("echo '"'Oye chico!'"'");
**	returns arr[] = {echo, "Oye chico!, NULL}
** the first '"' stays to signal the redirection parser not to consider
** any redirection in that string.
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
		}
		else
		{
			*(*(quotpos + 1)) = '\0';
			tab[++i] = ft_strdup(quotpos[0]);
			str = quotpos[1] + 1;
			while ((*str) && (*str == c))
				str++;
		}
	}
	if ((str > quotpos[1]) && (*str))
		tab[++i] = ft_strdup(str);
	else if ((*str))
		tab[++i] = ft_strdup(quotpos[0]);
}

char		**ft_split__quots(char *str, char c)
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
	*(*(quotpos + 1)) = '"';
	*(*quotpos) = '"';
	loop_table(table, str, c, quotpos);
	return (table);
}
