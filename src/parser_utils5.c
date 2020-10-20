/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleon-ca <aleon-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:07:54 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/10/19 19:08:12 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		**set_quotpos_arr(char *str)
{
	char	*ptr;
	char	**quotpos;

	quotpos = malloc(sizeof(char *) * 1);
	*quotpos = NULL;
	while ((ptr = smallest_non_zero(ft_strchr(str, '"'), ft_strchr(str, '\''))))
	{
		if ((str = ft_strchr(ptr + 1, *ptr)))
		{
			ft_add_str(&quotpos, ptr);
			ft_add_str(&quotpos, str);
			str++;
		}
		else
		{
			ft_add_str(&quotpos, ptr);
			break;
		}
	}
	return (quotpos);
}

int			count_not_quoted_char(char **quotpos, char *str, char c)
{
	int		i;
	char	temp;
	int		count;

	count = 0;
	i = 0;
	while (quotpos[i])
	{
		temp = *quotpos[i];
		*quotpos[i] = '\0';
		count += ft_strnchr(str, c);
		*quotpos[i] = temp;
		if ((quotpos[i + 1]))
		{
			str = quotpos[i + 1] + 1;
			i += 2;
		}
		else
		{
			str = quotpos[i] + 1;
			break;
		}
	}
	count += ft_strnchr(str, c);
	return (count);
}
