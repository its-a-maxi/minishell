/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/21 15:17:29 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_minishell(void)
{
	int i;

	i = 0;
	while (g_env[i])
		free(g_env[i++]);
	free(g_env);
	exit(0);
}

int				envp_len(char **envp)
{
	int len;

	len = -1;
	while (envp[++len])
		;
	return (len);
}

void			save_env(int argc, char **argv, char **envp)
{
	int i;
	int j;
	int count;

	i = -1;
	j = -1;
	count = envp_len(envp) + 1;
	(void)argc;
	(void)argv;
	g_env = (char**)ft_calloc(count, sizeof(char*));
	while (envp[++j])
	{
		if ((ft_strncmp("_=", envp[j], 2) == 0) && envp[j + 1])
			j++;
		if (!(g_env[++i] = ft_strdup(envp[j])))
			exit_minishell();
	}
	if (j - 1 > i && !(g_env[i + 1] = ft_strdup("_=./minishell")))
		exit_minishell();
}

char			*env_selector(char *env)
{
	int		len;
	char	*rst;
	int		i;

	i = -1;
	write(1, "hey\n", 4);
	while (env[++i] && (env[i] != ' ') && (env[i] != '\t') && (env[i] != '\'')
		&& (env[i] != '"'))
		;
	len = i;
	i = 0;
	while (g_env[i] && ft_strncmp(env, g_env[i], len) != 0)
		i++;
	if (!g_env[i] || g_env[i][len] != '=')
		rst = ft_strdup("");
	else
		rst = ft_substr(g_env[i], len + 1, ft_strlen(g_env[i]));
	return (rst);
}
