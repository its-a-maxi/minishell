/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:14:31 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/01 13:13:04 by alejandro        ###   ########.fr       */
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
printf("\tapp[%d]: %s", k, table[h].append_file[k]);
printf("\n");
	}
	free_command_tables(table, table_num);
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
