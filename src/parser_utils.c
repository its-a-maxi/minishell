/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/28 12:29:15 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_command_tables(t_command_table *table, int table_num)
{
		int		i;
		int		j;

		i = -1;
		while (++i < table_num)
		{
			j = -1;
			while (++j < table[i].simple_commands_num)
				full_free((void **)table[i].simple_commands[j],
						ft_arrlen(table[i].simple_commands[j]));
			free(table[i].simple_commands);
			if (table[i].input_file)
				free(table[i].input_file);
			if (table[i].output_file)
				free(table[i].output_file);
			if (table[i].append_file)
				free(table[i].append_file);
		}
		free(table);
}

char			*ft_str2chr(char *str, char c)
{
	int		i;

	i = -1;
	while ((str[++i]) && (str[i + 1]))
	{
		if ((str[i] == c) && (str[i + 1] == c))
			return (str + i + 1);
	}
	return (0);
}



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
