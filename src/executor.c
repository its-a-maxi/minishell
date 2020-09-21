/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 12:42:39 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		executor(t_command_table *table, int table_num)
{
	int		i;

	i = table_num - 1;
	while (++i < table_num)
	{
		//Ejecutar cada tabla de commandos
		ft_printf("table %d:", i);
		int j = -1;
		while (++j < table[i].simple_commands_num)
		{
			ft_printf("command %d: %s", j,
			table[i].commands[j].commands_name);
			int k = -1;
			while (++k < arguments_num)
			{
				ft_printf("arg %d: %s", k,
					table[i].commands[j].arguments[k]);
			}
		}
		ft_printf(";\n");
	}
	free(command_table);
}
