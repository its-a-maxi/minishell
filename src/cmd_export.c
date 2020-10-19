/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:24:48 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/19 12:41:16 by aleon-ca         ###   ########.fr       */
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
	int		count;
	int		i;
	int		j;

	count = 2;
	i = -1;
	while (g_env[++i])
		if (ft_strncmp(str, g_env[i], ft_find_char(str, '=') + 1) == 0)
			count = 1;
	i = -1;
	j = -1;
	temp = (char**)ft_calloc(envp_len(g_env) + count, sizeof(char*));
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
		export_no_arg(temp);
		return ;
	}
	while (arg[++i])
	{
		if (!quotes_handler(arg, i))
			return ;
		if (arg[i][0] == '=' || ft_strchr(arg[i], '\n'))
		{
			write(2, "\U0001F633 minishell: export: `", 25);
			write(2, arg[i], ft_strlen(arg[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		else if (ft_strchr(arg[i], '='))
			new_g_env(arg[i]);
	}
	return ;
}
