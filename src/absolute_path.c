/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:02:21 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/23 19:47:37 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **save_absolute_path()
{
    char    *temp;
    char    **path;
    int     i;
    int     j;
    int     count;

    i = -1;
    j = 0;
    count = 0;
    temp = env_selector("PATH");
    if (temp[ft_strlen(temp) - 1] != ':')
        temp = ft_add_char(temp, ':');
    while (temp[++i])
        if (temp[i] == ':')
            j++;
    path = (char**)ft_calloc(j + 1, sizeof(char*));
    i = -1;
    j = 0;
    while (temp[++i])
        if (temp[i] == ':')
        {
            path[count] = ft_substr(temp, j, i - j + 1);
            path[count++][i - j] = '/';
            j = i + 1;
        }
    free(temp);
    return(path);
}

int       is_absolute_path(char *str)
{
    struct stat sb;
    char **path;
    char *temp;
    int i;

    path = save_absolute_path();
    i = -1;
    while(path[++i])
    {
        temp = ft_strjoin(path[i], str);
        if(stat(temp, &sb) == 0)
        {
            str = temp;
            ft_printf("in -is_absolute_path- = \"%s\"\n", str);
            return (1);
        }
        free(temp);
    }
    return (0);
}