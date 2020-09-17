/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 08:35:48 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/11 12:56:27 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strchr(char *str, int c)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (str + i);
	}
	return (0);
}

static char		*mem_update_by_buff_join(int fd, char **mem, char *buff)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (mem[fd][++i])
		;
	j = -1;
	while (buff[++j])
		;
	temp = malloc(sizeof(char) * (i + j + 1));
	temp[i + j] = '\0';
	i = -1;
	while (mem[fd][++i])
		temp[i] = mem[fd][i];
	j = -1;
	while (buff[++j])
		temp[i + j] = buff[j];
	free(mem[fd]);
	mem[fd] = temp;
	free(buff);
	return (temp + i);
}

static int		lineread__mem_trunc(int fd, char **mem, char *nl, char **line)
{
	int		i;
	int		j;
	char	*temp;

	*nl = '\0';
	i = -1;
	while (mem[fd][++i])
		;
	*line = malloc(sizeof(char) * (i + 1));
	*(*line + i) = '\0';
	j = -1;
	while (mem[fd][++j])
		*(*line + j) = mem[fd][j];
	while (mem[fd][++i])
		;
	temp = malloc(sizeof(char) * (i - j));
	temp[i - j - 1] = '\0';
	i = j;
	while (mem[fd][++i])
		temp[i - j - 1] = mem[fd][i];
	free(mem[fd]);
	mem[fd] = temp;
	return (1);
}

static int		remaining_mem_update(int fd, char **mem, char **line)
{
	int		i;
	char	*nlpos;

	if ((nlpos = ft_strchr(mem[fd], '\n')))
		return (lineread__mem_trunc(fd, mem, nlpos, line));
	else
	{
		i = -1;
		while (mem[fd][++i])
			;
		*line = malloc(sizeof(char) * (i + 1));
		i = -1;
		while (mem[fd][++i])
			*(*line + i) = mem[fd][i];
		free(mem[fd]);
		mem[fd] = 0;
		return (0);
	}
}

int				get_next_line(int fd, char **line)
{
	int			bytes_read;
	char		*buff;
	char		*nl;
	static char	*mem[4096];

	if ((fd < 0) || !line || !(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!mem[fd])
	{
		mem[fd] = malloc(sizeof(char) * 1);
		mem[fd][0] = '\0';
	}
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		if ((nl = ft_strchr(mem_update_by_buff_join(fd, mem, buff), '\n')))
			return (lineread__mem_trunc(fd, mem, nl, line));
		buff = malloc(sizeof(char) * (BUFFER_SIZE));
	}
	if (buff)
		free(buff);
	if (bytes_read == 0)
		return (remaining_mem_update(fd, mem, line));
	return (-1);
}
