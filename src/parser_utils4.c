/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:32:42 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/19 09:51:52 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_add_str(char ***arrdir, char *str)
{
	int		arrlen;
	int		i;
	char	**temp;

	arrlen = ft_arrlen(*arrdir);
	temp = malloc(sizeof(char *) * (arrlen + 2));
	temp[arrlen + 1] = NULL;
	temp[arrlen] = str;
	i = -1;
	while (*(*arrdir + ++i))
		temp[i] = *(*arrdir + i);
	free(*arrdir);
	*arrdir = temp;
}

/*
** Removes the '"' or '\'' from possible remaining quot-encapsulated sentences.
**
** returns:		the array of strings resulted from the split call, minus any
**				remaining quotation character couple.
**
** parameter #1:	the address of an array of strings, which is modified.
*/


char		*smallest_non_zero(char *ptr1, char *ptr2)
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

void		remove_quots(char **strdir)
{
	int		i;
	char	*quotpos[2];
	char	*temp;

	i = -1;
	while (*(*strdir + ++i))
	{
		if ((quotpos[0] = smallest_non_zero(ft_strchr(*strdir, '"'),
			ft_strchr(*strdir, '\'')))
			&& (quotpos[1] = ft_strchr(quotpos[0] + 1, *quotpos[0])))
		{
			*quotpos[0] = '\0';
			*quotpos[1] = '\0';
			temp = ft_strjoin(*strdir, quotpos[0] + 1);
			free(*strdir);
			*strdir = temp;
		}
	}
}

/*
** Removes the possible empty strings after a ft_split call.
**
** returns:		the array of strings resulted from the split call, minus the
**				empty ones.
**
** parameter #1:	an array of strings
*/

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
