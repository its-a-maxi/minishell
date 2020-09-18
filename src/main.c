/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 12:33:23 by alejandro         #+#    #+#             */
/*   Updated: 2020/09/17 12:52:03 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		show_prompt(void)
{
	char	dir_str[4096 + 1];

	dir_str[4096] = '\0';
	getcwd(dir_str, 4096);
	write(1, dir_str, ft_strlen(dir_str));
}

void		signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		show_prompt();
		signal(SIGINT, signal_handler);
	}
}	

/*
** Initializes minishell
**
** return:	0 on completion
** param #1:	argc	argument count
** param #2:	argv	argument variables
** param #3:	envv	environment variables
*/

int		main()
{
	while (1)
	{
		show_prompt();
		signal(SIGINT, signal_handler);
		//get_input
		//caso de str vacia
		//split de los commands por ;
		//ejecutar los commands
		//Liberar cosas
		//Ver si returnearon error
	}
	//Liberar entorno
	return (0);
}
