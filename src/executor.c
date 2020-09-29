/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/29 10:15:50 by aleon-ca         ###   ########.fr       */
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
	int		h = -1;
//printf("command_table_num:%d\n", table_num);
	while (++h < table_num)
	{
printf("table[%d] with simple_commands_num: %d\n", h, table[h].simple_commands_num);
		int i = -1;
		while (++i < table[h].simple_commands_num)
		{
			int j = -1;
			while (table[h].simple_commands[i][++j])
				printf("\tsimple command %d arg %d: %s\n", i, j, table[h].simple_commands[i][j]);
		}
		int k = -1;
		while (++k < ft_arrlen(table[h].output_file))
printf("\tout[%d]: %s", k, table[h].output_file[k]);
		k = -1;
		while (++k < ft_arrlen(table[h].input_file))
printf("\tin[%d]: %s", k, table[h].input_file[k]);
		k = -1;
		while (++k < ft_arrlen(table[h].append_file))
printf("\tapp[%d]: %s\t", k, table[h].append_file[k]);
	}
}
