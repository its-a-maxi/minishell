/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/13 13:49:39 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input(t_command_table *t, int *i, int *fd_tmp, int *fd_std)
{
	if (!(t->input_files[i[1]][0]))
		fd_std[0] = dup(fd_tmp[0]);
	else
		fd_std[0] = open(t->input_files[i[1]][0], O_RDONLY);
	dup2(fd_std[0], 0);
	close(fd_std[0]);
}

static void	redirect_output(t_command_table *t, int *i, int *fd_tmp, int *std)
{
	int		fd_pipe[2];

	if (!(t->output_files[i[1]][0])
		&& !(t->append_files[i[1]][0]))
		std[1] = dup(fd_tmp[1]);
	else if ((t->append_files[i[1]][0]))
	{
		std[1] = open(t->append_files[i[1]][0], O_WRONLY);
		advance_ptr_eof(std[1]);
	}
	else if ((t->output_files[i[1]][0]))
	{
		std[1] = open(t->output_files[i[1]][0], O_WRONLY);
		overwrite_ptr_begin(std[1]);
	}
	if (i[1] != (t->simple_commands_num - 1))
	{
		pipe(fd_pipe);
		std[1] = fd_pipe[1];
		std[0] = fd_pipe[0];	
	}
	dup2(std[1], 1);
	close(std[1]);
}

static void	create_dummy_files(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
	{
		if (open(arr[i], O_CREAT) < 0)
			write(2, strerror(errno), ft_strlen(strerror(errno)));
	}
}


static void	restore_stdio(int *fd_tmp)
{
	dup2(fd_tmp[0], 0);
	dup2(fd_tmp[1], 1);
	close(fd_tmp[0]);
	close(fd_tmp[1]);
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
	int		fd_tmp[2];
	int		fd_std[2];

	i[0] = -1;
	while (++(i[0]) < table_num)
	{
		fd_tmp[0] = dup(0);
		fd_tmp[1] = dup(1);
		i[1] = -1;
		while (++(i[1]) < table[i[0]].simple_commands_num)
		{
			redirect_input(table + i[0], i, fd_tmp, fd_std);
			redirect_output(table + i[0], i, fd_tmp, fd_std);	
			create_dummy_files(table[i[0]].dummy_files[i[1]]);
			if ((is_built_in(table[i[0]].simple_commands[i[1]])))
				choose_and_execute(table[i[0]].simple_commands[i[1]]);
			else if ((is_start_executable_path
						(table[i[0]].simple_commands[i[1]][0])))
			{
				if (!(fork_and_check_error()))
					execute_executable(table[i[0]].simple_commands[i[1]]);
				waitpid(-1, NULL, 0);
			}
			else
			{
				write(2, "minishell: ", 11); 
				write(2, table[i[0]].simple_commands[i[1]],
					ft_strlen(table[i[0]].simple_commands[i[1]][0]));
				write(2, " command not found.\n", 20); 
				exit(0);
			}
		}
		restore_stdio(fd_tmp);
	}
	free_cmd_table(table, table_num);
}
