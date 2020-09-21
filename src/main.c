/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 11:54:40 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		show_prompt(void)
{
	char	dir_str[4096 + 1];

	dir_str[4096] = '\0';
	getcwd(dir_str, 4096);
	write(1, dir_str, ft_strlen(dir_str));
	write(1, " $ ", 3);
}

/*
** "control + c" signal doesn't exit the shell, but rather,
** it should exit the current child process or simply clean stdin
** before reading.
*/

void		signal_handler(int sig)
{
	if ((sig == SIGINT) || (sig == SIGQUIT))
	{
		write(1, "\n", 1);
		show_prompt();
	}
}

/*
** Initializes minishell
**
** return:	0 on completion
**
** param #1:	argc	argument count
** param #2:	argv	argument variables
** param #3:	envv	environment variables
*/

int			main(int argc, char **argv, char **envp)
{
	char				*input;
	t_command_table		*command_table;
	int					command_table_num;

	save_env(argc, argv, envp);
	while (1)
	{
		if (!(input = ft_calloc(1, sizeof(char))))
			return (0);
		show_prompt();
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		read_input(input);
		//caso de str vacia?
		commands = ft_split(input, ';');
		command_table_num = ft_arrlen(commands);
		command_table = tokenize(commands, command_table_num);
		executor(command_table, command_table_num);
		//Ver si returnearon error
	}
	//Liberar entorno
	return (0);
}
