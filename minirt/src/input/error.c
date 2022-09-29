/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:55:15 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/26 18:10:59 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	free_input(t_data *data)
{
	int	i;

	i = 0;
	if (data->shapes.sphere)
		free(data->shapes.sphere);
	if (data->shapes.cilinder)
		free(data->shapes.cilinder);
	if (data->shapes.plane)
		free(data->shapes.plane);
	if (data->shapes.cone)
		free(data->shapes.cone);
	if (data->shapes.cam)
		free(data->shapes.cam);
	if (data->shapes.light)
		free(data->shapes.light);
	if (data->mlx.img)
		free(data->mlx.img);
}

void	error(char *str, int *check, int exit_err)
{
	(*check)++;
	printf(KRED"%s\n" KNRM, str);
	if (exit_err)
		exit(1);
}

int	input_error(char *str, char *str2, int *check, int exit_err)
{
	(*check)++;
	printf(KRED"%s [%s]\n"KNRM, str, str2);
	if (exit_err)
		exit(1);
	return (0);
}

void	free_exit(t_data *data)
{
	free_input(data);
	exit(1);
}

int	ft_close(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}
