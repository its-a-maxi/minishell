/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 11:24:48 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/09/24 12:21:05 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     free_double(char **str)
{
    int i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str);
}

static void     new_g_env(char *str)
{
    char    **temp;
    char    **buff;
    int i;

    i = -1;
    temp = (char**)ft_calloc(envp_len(g_env) + 2, sizeof(char*));
    while (g_env[++i] && (g_env[i + 1][0] != '_' && g_env[i + 1][1] != '='))
	    if(!(temp[i] = ft_strdup(g_env[i])))
		    exit_minishell();
    if(!(temp[++i] = ft_strdup(str)))
	    exit_minishell();
    i++;
    if(!(temp[i] = ft_strdup(g_env[i - 1])))
	    exit_minishell();
    buff = g_env;
    g_env = temp;
    free_double(buff);
}

static int      ft_check(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (str[i] != 0 && str[i + 1] == '=')
            return (1);
    return (0);
}

void            cmd_export(char **arg)
{
    int i;

    i = 0;
    if (!arg[1])
    {
        while (g_env[i] || (g_env[i][0] != '_' && g_env[i][1] != '='))
        {
            write(1, g_env[i], ft_strlen(g_env[i]));
            write(1, "\n", 1);
            i++;
        }
        return;
    }
    while (arg[++i])
    {
        if (ft_check(arg[i]))
            new_g_env(arg[i]);
    }
    return;
}