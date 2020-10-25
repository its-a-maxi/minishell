/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:02:21 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/25 11:16:36 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**save_absolute_path(void)
{
	char	*temp;
	char	**path;
	int		i;
	int		j;
	int		count;

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
	return (path);
}

int		is_absolute_path(char **strdir)
{
	struct stat		sb;
	char			**path;
	char			*temp;
	int				i;

	path = save_absolute_path();
	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], *strdir);
		if (stat(temp, &sb) == 0)
		{
			free(*strdir);
			*strdir = temp;
			free_double(path);
			return (1);
		}
		free(temp);
	}
	free_double(path);
	return (0);
}
