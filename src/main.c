/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/21 09:22:23 by aleon-ca         ###   ########.fr       */
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

static char	*ft_add_char(char *str, char c)
{
	char	*rst;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	rst = ft_calloc(len + 2, sizeof(char));
	while (i < len)
	{
		rst[i] = str[i];
		i++;
	}
	rst[i] = c;
	free(str);
	return (rst);
}

/*
** Reads shell's stdin input one byte at a time until a '\n' is found
** If ctrl-D (EOF) is invoked, the shell is terminated.
*/


static void	read_input(char *input)
{
	char	buff[1];
	int		bytes_read;
	
	while ((bytes_read = read(0, buff, 1)) && buff[0] != '\n')
		input = ft_add_char(input, buff[0]);
	input = ft_add_char(input, '\0');
	if (!bytes_read)
	{
		free(input);
		write(1, "\n", 1);
		exit(0);
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

int			main()
{
	char	*input;

	while (1)
	{
		if (!(input = ft_calloc(1, sizeof(char))))
			return(0);
		show_prompt();
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		read_input(input);
		//caso de str vacia
		//split de los commands por ;
		//ejecutar los commands
		//Liberar cosas
		//Ver si returnearon error
	}
	//Liberar entorno
	return (0);
}
