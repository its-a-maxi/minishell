/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 09:39:50 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/19 09:58:49 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			read_input_subshell(char **input, char c, char *ptr)
{
	char		buff[1];
	int			bytes_read;
	char		*temp;

	*ptr = '\0';
	temp = ft_strjoin(*input, ptr + 1);
	free(*input);
	*input = temp;
	*input = ft_add_char(*input, '\n');
	while ((bytes_read = read(0, buff, 1)) && buff[0] != c)
		*input = ft_add_char(*input, buff[0]);
	if (!bytes_read)
		write(2, "minishell: unexpected EOF while looking for matching quote\n",
			60);
	return (bytes_read);
}
