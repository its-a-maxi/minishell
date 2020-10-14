/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/14 10:51:46 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input(t_command_table *t, int *i, int *fd)
{
	if (!(t->input_files[i[1]][0]))
		fd[2] = dup(fd[0]);
	else
		fd[2] = open(t->input_files[i[1]][0], O_RDONLY);
	dup2(fd[2], 0);
	close(fd[2]);
}

static void	redirect_output(t_command_table *t, int *i, int *fd, int *fd_pipe)
{
	if (!(t->output_files[i[1]][0])
		&& !(t->append_files[i[1]][0]))
		fd[3] = dup(fd[1]);
	else if ((t->append_files[i[1]][0]))
		fd[3] = open(t->append_files[i[1]][0], O_CREAT | O_WRONLY | O_APPEND,
			S_IWUSR | S_IRUSR);
	else if ((t->output_files[i[1]][0]))
		fd[3] = open(t->output_files[i[1]][0], O_CREAT | O_WRONLY | O_TRUNC,
			S_IWUSR | S_IRUSR);
	if (i[1] != (t->simple_commands_num - 1))
	{
		pipe(fd_pipe);
		fd[3] = fd_pipe[1];
		fd[2] = fd_pipe[0];	
	}
	dup2(fd[3], 1);
	close(fd[3]);
}

static void	create_dummy_files(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (open(arr[i], O_CREAT, S_IWUSR | S_IRUSR) < 0)
			write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
}


static void	restore_stdio(int *fd)
{
	//fd[0] es tmp[0]; fd[1] es tmp[1]; fd[2] es std[0]; fd[3] std[1]
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void		executor(t_command_table *table, int table_num)
{
	int		h = -1;
	while (++h < table_num)
	{
printf("table[%d] with simple_commands_num: %d\n", h, table[h].simple_commands_num);
		int i = -1;
		while (++i < table[h].simple_commands_num)
		{
			int j = -1;
			while (table[h].simple_commands[i][++j])
			{
				printf("\tsimple command %d arg %d: %s\n", i, j,
					table[h].simple_commands[i][j]);
			}
			int k = -1;
			while ((table[h].input_files[i][++k]))
				printf("input [%d] of simple_command %d: %s\n", k, i, table[h].input_files[i][k]);
			k = -1;
			while ((table[h].output_files[i][++k]))
				printf("output [%d] of simple_command %d: %s\n", k, i, table[h].output_files[i][k]);
			k = -1;
			while ((table[h].append_files[i][++k]))
				printf("append [%d] of simple_command %d: %s\n", k, i, table[h].append_files[i][k]);
			k = -1;
			while ((table[h].dummy_files[i][++k]))
				printf("dummy [%d] of simple_command %d: %s\n", k, i, table[h].dummy_files[i][k]);
		}
	}
	//Aqui empieza el executor de verdad
	int		i[2];
	int		fd_pipe[2];
	int		fd[4];

	i[0] = -1;
	while (++(i[0]) < table_num)
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
		i[1] = -1;
		while ((table[i[0]].simple_commands[++(i[1])]))
		{
			redirect_input(table + i[0], i, fd);
			redirect_output(table + i[0], i, fd, fd_pipe);	
			create_dummy_files(table[i[0]].dummy_files[i[1]]);
			if ((is_built_in(table[i[0]].simple_commands[i[1]])))
				choose__exec(table[i[0]].simple_commands[i[1]], table + i[0]);
			else if ((is_start_exec_path(table[i[0]].simple_commands[i[1]][0])))
				launch_exec(table[i[0]].simple_commands[i[1]]);
			else if ((table[i[0]].simple_commands[i[1]][0] != NULL))
				cmd_not_found(table[i[0]].simple_commands[i[1]][0]);
		}
		restore_stdio(fd);
	}
	free_cmd_table(table, table_num);
}
