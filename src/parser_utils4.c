/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandroleon <aleon-ca@student.42.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 16:58:04 by alejandro         #+#    #+#             */
/*   Updated: 2020/10/01 17:26:49 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		uptin(t_command_table *t, int j, int n)
{
	char	*ptr;
	int	i;

	i = -1;
	while ((ptr = t->simple_commands[j][++i]))
	{
		if ((ft_strchr(ptr, '<')))
		{
			n++;
			t->input_file[n] = (ft_strlen(ptr) != 1) ?
				ft_strdup(ptr+ 1) :
					ft_strdup(t->simple_commands[j][i + 1]);
			rmin(t, i, j);
			if ((check_redirection_error(t->input_file[n])))
				return (1);
			i = -1;
		}
	}
	return (0);
}
int		upout(t_command_table *t, int j, int outcount)
{
	char	*ptr;
	int	i;

	i = -1;
	while ((ptr = t->simple_commands[j][++i]))
	{	
		if (!(ft_str2chr(ptr, '>')) && (ft_strchr(ptr, '>')))
		{
			outcount++;
			t->output_file[outcount] = (ft_strlen(ptr) != 1) ?
			ft_strdup(ptr + 1) :
				ft_strdup(t->simple_commands[j][i + 1]);
			rmout(t, i, j);	
			if ((check_redirection_error(t->output_file[outcount])))
				return (1);
			i = -1;
		}
	}
	return (0);
}

int		upapp(t_command_table *t, int j, int appcount)
{
	char	*ptr;
	int	i;

	i = -1;
	while ((ptr = t->simple_commands[j][++i]))
	{
		if ((ft_str2chr(ptr, '>')))
		{
			appcount++;
			t->append_file[appcount] = (ft_strlen(ptr) > 2) ?
			ft_strdup(ptr + 2) : ft_strdup(t->simple_commands
				[j][i + 1]);
			rmapp(t, i, j);
			if ((check_redirection_error(t->append_file[appcount])))
				return (1);
			i = -1;
		}
	}
	return (0);
}
