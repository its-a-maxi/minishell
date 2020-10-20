/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/20 11:49:51 by aleon-ca         ###   ########.fr       */
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

static int	any_command_table_empty(char **table, char **input)
{
	int		i;

	i = -1;
	while (table[++i])
	{
		if ((table[i][0] == '\0') && (i > 1))
		{
			write(2, "\U0001F633 minishell: syntax error.\n", 31);
			free(*input);
			*input = NULL;
			full_free((void **)table, ft_arrlen(table));
			return (1);
		}
	}
	return (0);
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

	signal(SIGQUIT, signal_handler);
	save_env(argc, argv, envp);
	while (1)
	{
		if (!(input = ft_calloc(1, sizeof(char))))
			return (EXIT_FAILURE);
		show_prompt();
		signal(SIGINT, signal_handler);
		read_input(&input);
		commands = ft_split__quots(input, ';');
		if (any_command_table_empty(commands, &input))
			continue;
		commands = remove_empty_str(commands);
		if (!(command_table = malloc(sizeof(t_command_table) *
			ft_arrlen(commands))))
			return (EXIT_FAILURE);
		if (!(tokenize(commands, command_table, ft_arrlen(commands))))
			executor(command_table, ft_arrlen(commands));
		free(input);
	}
	return (0);
}
