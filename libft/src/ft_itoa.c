/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:26:03 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/25 16:06:52 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_add_char(char **strdir, char c)
{
	int		size;
	int		i;
	char	*temp;

	size = ft_strlen(*strdir);
	temp = malloc(sizeof(char) * (size + 2));
	temp[size + 1] = '\0';
	i = -1;
	while (++i < size)
		temp[i] = *(*strdir + i);
	temp[i] = c;
	free(*strdir);
	*strdir = temp;
}

static void	ft_putnbr(char **result, int n)
{
	if (n >= 10)
		ft_putnbr(result, n / 10);
	ft_add_char(result, n + 48);
}

char		*ft_itoa(int n)
{
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = ft_calloc(1, sizeof(char));
	if (n < 0)
	{
		ft_add_char(&result, '-');
		n *= -1;
	}
	ft_putnbr(&result, n);
	return (result);
}
