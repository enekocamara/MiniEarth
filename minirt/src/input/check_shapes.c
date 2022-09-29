/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:22:41 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/14 17:30:27 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	check_sphere(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 4)
	{
		if (len == 5)
			check_double(temp[4], check);
		else
			input_error(KRED "KO! Input error", line, check, 0);
	}
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_double(temp[2], check);
	check_values_range(temp[2], check, 0, __DBL_MAX__);
	check_three(temp[3], check);
	c_check_values_range(temp[3], check, 0, 255);
	free2d(temp);
	data->shapes.max_s++;
}

void	check_plane(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 4)
	{
		if (len == 5)
			check_double(temp[4], check);
		else
			input_error("KO! Input error", line, check, 0);
	}
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[2], check);
	c_check_values_range(temp[2], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[3], check);
	c_check_values_range(temp[3], check, 0, 255);
	free2d(temp);
	data->shapes.max_p++;
}

void	check_cylinder(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 6)
	{
		if (len == 7)
			check_double(temp[6], check);
		else
			input_error(KRED "KO! Input error", line, check, 0);
	}
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[2], check);
	c_check_values_range(temp[2], check, -__DBL_MAX__, __DBL_MAX__);
	check_double(temp[3], check);
	check_values_range(temp[3], check, 0, __DBL_MAX__);
	check_double(temp[4], check);
	check_values_range(temp[4], check, 0, __DBL_MAX__);
	check_three(temp[5], check);
	c_check_values_range(temp[5], check, 0, 255);
	free2d(temp);
	data->shapes.max_cy++;
}

void	check_cone(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 4)
	{
		if (len == 5)
			check_double(temp[4], check);
		else
			input_error(KRED "KO! Input error", line, check, 0);
	}
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[2], check);
	c_check_values_range(temp[2], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[3], check);
	c_check_values_range(temp[3], check, 0, 255);
	free2d(temp);
	data->shapes.max_cn++;
}
