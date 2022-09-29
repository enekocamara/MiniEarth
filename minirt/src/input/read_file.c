/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:16:07 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/01 16:53:39 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static char	*append(char *str, char buff, int *size, int *check)
{
	char	*final;
	int		i;

	(*size)++;
	final = malloc((*size) + 1);
	if (!final)
	{
		error("Malloc error", check, 0);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		final[i] = str[i];
		i++;
	}
	final[i] = buff;
	final[i + 1] = '\0';
	free (str);
	return (final);
}

char	*get_file(int fd, int *check)
{
	char	*str;
	int		filled;
	int		size;

	filled = 1;
	size = 0;
	str = malloc(1);
	if (!str)
		error("Malloc error", check, 0);
	str[0] = '\0';
	return (read_in_loop(&str, fd, filled, check));
}

char	*read_in_loop(char **str, int fd, int filled, int *check)
{
	char	buff;
	int		size;

	size = 0;
	while (filled != 0)
	{
		filled = read(fd, &buff, 1);
		if (filled < 0)
		{
			free (str);
			error("Read error", check, 0);
		}
		if (filled == 0)
		{
			if (buff == '\0')
			{
				free (str);
				return (NULL);
			}
			else
				return (*str);
		}
		*str = append(*str, buff, &size, check);
	}
	return (*str);
}
