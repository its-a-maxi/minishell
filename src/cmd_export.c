/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:24:48 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/14 12:20:46 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*new_arg(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(old) + 3, sizeof(char));
	while (old[i])
	{
		new[j++] = old[i++];
		if (old[i - 1] == '=')
		{
			if (!old[i])
				new[j++] = '"';
			new[j++] = '"';
		}
		else if (!old[i])
			new[j++] = '"';
	}
	new[j] = 0;
	return (new);
}

static char		**no_arg(void)
{
	char	**cpy;
	char	*temp;
	int		i;
	int		j;

	i = -1;
	cpy = (char**)ft_calloc(envp_len(g_env), sizeof(char*));
	while (g_env[++i] && ft_strncmp("_=", g_env[i], 2) != 0)
		cpy[i] = new_arg(g_env[i]);
	i = -1;
	while (cpy[++i])
	{
		j = i;
		while (cpy[++j])
			if (ft_strcmp(cpy[i], cpy[j]) > 0)
			{
				temp = cpy[i];
				cpy[i] = cpy[j];
				cpy[j] = temp;
			}
	}
	return (cpy);
}

static void		new_g_env2(char *str, char **temp, int i, int j)
{
	int sum;

	sum = 0;
	while (g_env[++j])
		if (ft_strncmp(str, g_env[j], ft_find_char(str, '=') + 1) == 0)
		{
			if (!(temp[j] = ft_strdup(str)))
				exit_minishell();
			sum = 1;
			break ;
		}
	if (!g_env[j])
		if (!(temp[i] = ft_strdup(str)))
			exit_minishell();
	while (g_env[i++])
	{
		if (!(temp[i - sum] = ft_strdup(g_env[i - 1])))
			exit_minishell();
	}
	return ;
}

static void		new_g_env(char *str)
{
	char	**temp;
	char	**buff;
	int		i;
	int		j;

	i = -1;
	j = -1;
	temp = (char**)ft_calloc(envp_len(g_env) + 2, sizeof(char*));
	while (g_env[++i] && ft_strncmp("_=", g_env[i], 2) != 0)
		if (!(temp[i] = ft_strdup(g_env[i])))
			exit_minishell();
	new_g_env2(str, temp, i, j);
	buff = g_env;
	g_env = temp;
	free_double(buff);
}

void			cmd_export(char **arg)
{
	int		i;
	char	**temp;

	i = 0;
	if (!arg[1])
	{
		temp = no_arg();
		while (temp[i])
		{
			write(1, "declare -x ", 11);
			write(1, temp[i], ft_strlen(temp[i]));
			write(1, "\n", 1);
			i++;
		}
		free_double(temp);
		return ;
	}
	while (arg[++i])
	{
		if (arg[i][0] == '=')
			write(2, "minishell: export: `=': not a valid identifier\n", 47);
		else if (ft_strchr(arg[i], '='))
			new_g_env(arg[i]);
	}
	return ;
}
