/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/22 08:47:15 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** Runs the binary file by creating a new process and handles signals in case
** of interruptions then returns whether it executed successfully or not
**
** @param		path	The path to the binary file
** @param		args	The arguments to pass to the system command
** @return		-1 on failure, 1 on success
*/
//
//static int		run_cmd(char *path, char **args)
//{
//	pid_t	pid;
//
//	pid = fork();
//	signal(SIGINT, proc_signal_handler);
//	if (pid == 0)
//		execve(path, args, g_envv);
//	else if (pid < 0)
//	{
//		free(path);
//		ft_putendl("Fork failed to create a new process.");
//		return (-1);
//	}
//	wait(&pid);
//	if (path)
//		free(path);
//	return (1);
//}

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
