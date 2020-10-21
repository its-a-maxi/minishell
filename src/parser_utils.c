/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 13:19:35 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_add_char(char *str, char c)
{
	char	*rst;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	rst = ft_calloc(len + 2, sizeof(char));
	while (i < len)
	{
		rst[i] = str[i];
		i++;
	}
	rst[i] = c;
	free(str);
	return (rst);
}

/*
** Reads shell's stdin input one byte at a time until a '\n' is found
** If ctrl-D (EOF) is invoked, the shell is terminated.
*/

void			read_input(char **input)
{
	char	buff[1];
	int		bytes_read;

	while ((bytes_read = read(0, buff, 1)) && buff[0] != '\n')
		*input = ft_add_char(*input, buff[0]);
	*input = ft_add_char(*input, '\0');
	if (!bytes_read)
	{
		free(*input);
		exit_minishell();
	}
}

void			resize_arr_skip_pos(char ***arr, int pos)
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
