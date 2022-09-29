/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:00:43 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/29 16:20:35 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGH, "MINIRT");
}

void	create_threat(t_data *data)
{
	data->mutex = malloc(sizeof(pthread_t) * THREADS);
}

void	set_earth(t_data *data)
{
	int	x = 8192;
	int	y = 4096;

	t_earth *temp;
	temp = (t_earth *)malloc(sizeof(t_earth));
	data->shapes.earth = temp;
	data->shapes.earth->day.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/skybox/texture/earth8k.xpm", &x, &y);
	data->shapes.earth->day.add = (int *)mlx_get_data_addr(
			data->shapes.earth->day.img,
			&data->shapes.earth->day.bpp, &data->shapes.earth->day.w,
			&data->shapes.earth->day.endian);
	data->shapes.earth->day.h = data->shapes.earth->day.w / 2;
	data->shapes.earth->night.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/skybox/texture/earth_night8k.xpm", &x, &y);
	data->shapes.earth->night.add = (int *)mlx_get_data_addr(
			data->shapes.earth->night.img,
			&data->shapes.earth->night.bpp, &data->shapes.earth->night.w,
			&data->shapes.earth->night.endian);
	data->shapes.earth->night.h = data->shapes.earth->night.w / 2;
	data->shapes.earth->clouds.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/skybox/texture/earth_clouds8k.xpm", &x, &y);
	data->shapes.earth->clouds.add = (int *)mlx_get_data_addr(
			data->shapes.earth->clouds.img,
			&data->shapes.earth->clouds.bpp, &data->shapes.earth->clouds.w,
			&data->shapes.earth->clouds.endian);
	data->shapes.earth->clouds.h = data->shapes.earth->clouds.w / 2;
	data->shapes.earth->index = 0;
}

void	set_data(t_data *data, char *argv[])
{
	init_mlx(data);
	init_vars(data);
	get_input(data, argv[1], 0);
	get_potential(&data->shapes);
	init_called(&data->shapes);
	if (data->shapes.skybox->active)
		set_skybox(data);
	if (EARTH)
		set_earth(data);
	create_threat(data);
}

void	init_vars(t_data *data)
{
	data->shapes.skybox = NULL;
	data->shapes.max_s = 0;
	data->shapes.max_p = 0;
	data->shapes.max_cy = 0;
	data->shapes.max_l = 0;
	data->shapes.max_c = 0;
	data->shapes.max_cn = 0;
	data->mlx.img_index = 0;
}
