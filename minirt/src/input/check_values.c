/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:21:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/26 18:11:24 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	check_rt(char *str, int *check)
{
	int	end;

	end = ft_strlen(str);
	if (end <= 3)
		error("KO! Input file name error", check, 1);
	if (!ft_strcmp(str + end - 3, ".rt"))
		error("KO! Input file name error", check, 1);
}

int	check_double(char *num, int *check)
{
	int	dot;
	int	i;

	dot = 0;
	i = 0;
	while (num[i] && (ft_isdigit(num[i]) || num[i] == '.' || num[i] == '-'))
	{
		if (num[i] == '.')
			dot++;
		i++;
	}
	if (num[i] || dot > 1)
		input_error("KO! Double NOT VALID", num, check, 0);
	return (0);
}

int	check_three(char *str, int *check)
{
	char	**temp;
	int		i;
	int		comma;

	i = -1;
	comma = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			comma++;
	}
	if (comma != 2)
		return (input_error("KO! Input error", str, check, 0));
	temp = ft_split(str, ',');
	if (!temp || !temp[1] || !temp[1] || !temp[2] || temp[3])
		return (input_error("KO! Invalid vector, coord or rgb", str, check, 0));
	i = -1;
	while (temp[++i])
	{
		if (check_double(temp[i], check))
			input_error("KO! Invalid vector, coord or rgb", str, check, 0);
	}
	free2d(temp);
	return (0);
}

void	check_dbl_range(double value, int *check, double min, double max)
{
	char	*str;

	if (value < min || value > max)
	{
		str = ft_dtoa(value);
		input_error("KO! Value out of range", str, check, 0);
		free(str);
	}
}

void	check_values_range(char *str, int *check, double min, double max)
{
	double	hold;

	hold = ft_atoi_double(str);
	check_dbl_range(hold, check, min, max);
}
