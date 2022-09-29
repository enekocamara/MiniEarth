/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:08:18 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 11:33:53 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	check_ambient_light(char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 3)
		input_error("KO! Input error", line, check, 0);
	check_double(temp[1], check);
	check_values_range(temp[1], check, 0, 1);
	check_three(temp[2], check);
	c_check_values_range(temp[2], check, 0, 255);
	free2d(temp);
}

void	check_camera(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 4)
		input_error("KO! Input error", line, check, 0);
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_three(temp[2], check);
	c_check_values_range(temp[2], check, -__DBL_MAX__, __DBL_MAX__);
	check_double(temp[3], check);
	check_values_range(temp[3], check, 1, 179);
	free2d(temp);
	data->shapes.max_c++;
}

void	check_light(t_data *data, char *line, int *check)
{
	char	**temp;
	int		len;

	temp = ft_split_str(line, " 	");
	len = ft_strlen2d((const char **)temp);
	if (len != 4)
		input_error(KRED "KO! Input error", line, check, 0);
	check_three(temp[1], check);
	c_check_values_range(temp[1], check, -__DBL_MAX__, __DBL_MAX__);
	check_double(temp[2], check);
	check_values_range(temp[2], check, 0, 1);
	check_three(temp[3], check);
	c_check_values_range(temp[3], check, 0, 255);
	free2d(temp);
	data->shapes.max_l++;
}

void	c_check_values_range(char *str, int *check, double min, double max)
{
	t_couple	hold;

	hold = get_couple(str);
	check_dbl_range(hold.x, check, min, max);
	check_dbl_range(hold.y, check, min, max);
	check_dbl_range(hold.z, check, min, max);
}
