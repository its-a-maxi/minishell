/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:29:44 by alejandro         #+#    #+#             */
/*   Updated: 2020/09/28 13:20:13 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_redirect_from_args(t_command_table *table, int i, int c)
{
	char	**temp;
	char	**arr;
	int	len;
	int	j;
//Aqui debemos actualizar, quitando solo las redirecciones del array del
// simple command.
	arr = table->simple_commands[table->simple_commands_num - 1];
	len = ft_strlen(arr[i]);
	temp = malloc(sizeof(char *) * (ft_arrlen(arr) - 1
		- 1 * (((len > 1) && (c != 'A'))
		|| ((len > 2) && (c == 'A')))));
	j = -1;
	while (arr[++j])
	{
		if ((j == i) || ((((len > 1) && (c != 'A'))
			|| ((len > 2) && (c == 'A'))) && (j == i + 1)))
			continue;
		temp[j] = ft_strdup(arr[j]);
	}
	temp[j] = NULL;
printf("Removed redirection from args. Now simple_command array is:\n");
	full_free((void **)arr, ft_arrlen(arr));
	arr = temp;
int k = -1;while (table->simple_commands[table->simple_commands_num - 1][++k]){printf("%s\n", table->simple_commands[table->simple_commands_num - 1][k]);}
}

void		set_inredirect(t_command_table *table, int incount)
{
	int	i;
	char	*ptr;

	table->input_file = malloc(sizeof(char *) * (incount + 1));
	table->input_file[incount] = NULL;
	incount = -1;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{
		if ((ft_strchr(ptr, '<')))
		{
			incount++;
			table->input_file[incount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'I');
		}	
	}
}

void		set_outredirect(t_command_table *table, int outcount)
{
	int	i;
	char	*ptr;

	table->output_file = malloc(sizeof(char *) * (outcount + 1));
	table->output_file[outcount] = NULL;
	outcount = -1;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{	
		if (!(ft_str2chr(ptr, '>')) && (ft_strchr(ptr, '>')))
		{
			outcount++;
			table->output_file[outcount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'O');	
		}
	}
}

void		set_appredirect(t_command_table *table, int appcount)
{
	int	i;
	char	*ptr;

	table->append_file = malloc(sizeof(char *) * (appcount + 1));
	table->append_file[appcount] = NULL;
	appcount = 0;
	i = -1;
	while ((ptr = table->simple_commands
		[table->simple_commands_num - 1][++i]))
	{
		if ((ft_str2chr(ptr, '>')))
		{
			appcount++;
			table->append_file[appcount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr) : ft_strdup(table->simple_commands
				[table->simple_commands_num - 1][i + 1]);
			remove_redirect_from_args(table, i, 'A');
		}
	}
}
