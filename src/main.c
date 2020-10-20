/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/19 18:46:52 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		show_prompt(void)
{
	char	dir_str[4096 + 1];
	char	*prompt;

	dir_str[4096] = '\0';
	getcwd(dir_str, 4096);
	write(1, dir_str, ft_strlen(dir_str));
	write(1, " ", 1);
	prompt = "\U0001F44C";
	write(1, prompt, 5);
	write(1, " ", 1);
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
	char				**commands;
	t_command_table		*command_table;

	save_env(argc, argv, envp);
	while (1)
	{
		if (!(input = ft_calloc(1, sizeof(char))))
			return (EXIT_FAILURE);
		show_prompt();
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		read_input(&input);
		commands = remove_empty_str(ft_split__quots(input, ';'));
int k = -1; while (commands[++k])
	ft_printf("command tables: %s\n", commands[k]);
		if (!(command_table = malloc(sizeof(t_command_table) *
			ft_arrlen(commands))))
			return (EXIT_FAILURE);
		if (!(tokenize(commands, command_table, ft_arrlen(commands))))
			executor(command_table, ft_arrlen(commands));
		free(input);
	}
	return (0);
}
