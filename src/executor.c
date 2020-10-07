/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/07 13:04:14 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_start_executable_path(char *str)
{
	if (ft_strlen(str) <= 2)
		return (0);
	if (str[0] == '.')
	{
		if ((str[1] == '.') && (str[2] == '/'))
			return (1);
		else if (str[1] == '/')
			return (1);
		else
			return (0);
	}
	else if ((str[0] == '~') && (str[1] == '/'))
		return (1);
	return (0);
}

static void	choose_and_execute(char **arr)
{
	if (!(ft_strcmp(arr[0], "echo")))
		cmd_echo(arr);
	else if (!(ft_strcmp(arr[0], "cd")))
		cmd_cd(arr);
	else if (!(ft_strcmp(arr[0], "pwd")))
		cmd_pwd(arr);
	else if (!(ft_strcmp(arr[0], "export")))
		cmd_export(arr);
	else if (!(ft_strcmp(arr[0], "unset")))
		cmd_unset(arr);
	else if (!(ft_strcmp(arr[0], "env")))
		cmd_env(arr);
	else if (!(ft_strcmp(arr[0], "exit")))
		exit_minishell();
	else if ((is_start_executable_path(arr[0])))	
		ft_printf("Executable path\n");
		//execute_executable(arr);
	else
		ft_printf("minishell: %s: command not found\n", arr[0]);
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
choose_and_execute(table[h].simple_commands[i]);
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
/*	int		i[2];
	int		fd_tmp[2];
	int		fd_pipe[2];
	int		fd_std[2];
	int		ret;

	i[0] = -1;
	while (++(i[0]) < table_num)
	{
		fd_tmp[0] = dup(0);
		fd_tmp[1] = dup(1);
		i[1] = -1;
		while (table->simple_commands[++(i[1])])
		{
			if (!(table->input_files[i[1]]))
				fd_std[0] = dup(fd_tmp[0]);
			else
				fd_std[0] = open(table->input_files[i[1]][0], O_RDONLY);
			dup2(fd_std[0], 0);
			close(fd_std[0]);
			if (!(table->output_files[i[1]]))
			{
				pipe(fd_pipe);
				fd_std[1] = fd_pipe[1];
				fd_std[0] = fd_pipe[0];	
			}
			else
				fd_std[1] = open(table->output_files[i[1]][0], O_WRONLY);
			dup2(fd_std[1], 1);
			close(fd_std[1]);
			if ((ret = fork()) < 0)
				fork_error();
			else if (ret == 0)
			{
				choose_and_execute(table->simple_commands[i[1]]);
				exit(0);
			}
		}
		dup2(fd_tmp[0], 0);
		dup2(fd_tmp[1], 1);
		close(fd_tmp[0]);
		close(fd_tmp[1]);
		waitpid(-1, NULL, 0);
	}*/
	//Liberar al final lo guardado.
	free_cmd_table(table, table_num);
}


/* EXAMPLE

 void		execute(char ***arg)
 {
	//save in/out
	int tmpin;
	int tmpout;
	int fdin;
	int ret;
	int fdout;
	int i;
	int fdpipe[2];
 
	i = 0;
	tmpin = dup(0);
	tmpout = dup(1);
	//set the initial input
	if (infile)
		fdin = open(infile, O_READ); 
	else
	// Use default input
		fdin = dup(tmpin);
	
	while (arg[i++])
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (!arg[i])
		{
			// Last simple command 
			if (outfile)
				fdout = open(outfile,â€¦â€¦);
			else
			// Use default output
				fdout = dup(tmpout);
		}
		else
		{
			// Not last 
			//simple command
			//create pipe
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
		dup2(fdout, 1);
		close(fdout);
		// Create child process
		ret = fork();
		if (ret == 0)
		{
			execvp(scmd[i].args[0], scmd[i].args);
			perror(â€œexecvpâ€);
			_exit(1);
		}
	}
	//restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	// Wait for last command
	waitpid(ret, NULL);
}
*/
