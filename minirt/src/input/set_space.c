/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:32:34 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:11:37 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	set_ambient_light(t_data *data, char *line)
{
	char		**values;
	t_ambient_l	*temp;

	temp = (t_ambient_l *)malloc(sizeof(t_ambient_l));
	values = ft_split(line, ' ');
	data->shapes.ambient_l = temp;
	data->shapes.ambient_l->range = ft_atoi_double(values[1]);
	data->shapes.ambient_l->color = col_to_01(get_couple(values[2]));
}

void	set_axis_cam(t_data *data, int i)
{
	t_couple	temp_up;

	if (data->shapes.cam[i]->direction.y == 1
		&& data->shapes.cam[i]->direction.x == 0
		&& data->shapes.cam[i]->direction.z == 0)
		temp_up = vector(0, 0, -1);
	else if (data->shapes.cam[i]->direction.y == -1
		&& data->shapes.cam[i]->direction.x == 0
		&& data->shapes.cam[i]->direction.z == 0)
		temp_up = vector(0, 0, 1);
	else
		temp_up = vector(0, 1, 0);
	data->shapes.cam[i]->right = c_mul(normalized(cross(
					data->shapes.cam[i]->direction, temp_up)), -1);
	data->shapes.cam[i]->up = c_mul(normalized(cross(
					data->shapes.cam[i]->right,
					data->shapes.cam[i]->direction)), -1);
}

void	set_camera(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_cam	*temp;

	temp = (t_cam *)malloc(sizeof(t_cam));
	if (!i)
		i = 0;
	values = ft_split_str(line, " 	");
	data->shapes.cam[i] = temp;
	data->shapes.cam[i]->origin = get_couple(values[1]);
	data->shapes.cam[i]->direction = normalized(get_couple(values[2]));
	data->shapes.cam[i]->fov = ft_atoi_double(values[3]);
	data->shapes.cam[i]->ratio = WIDTH / (double)HEIGH;
	data->shapes.cam[i]->w = tan((data->shapes.cam[i]->fov * M_PI / 360));
	data->shapes.cam[i]->h = data->shapes.cam[i]->w / WIDTH * HEIGH;
	set_axis_cam(data, i);
	i++;
}

void	set_light(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_light	*temp;

	temp = (t_light *)malloc(sizeof(t_light));
	if (!i)
		i = 0;
	values = ft_split(line, ' ');
	data->shapes.light[i] = temp;
	data->shapes.light[i]->origin = get_couple(values[1]);
	data->shapes.light[i]->range = ft_atoi_double(values[2]);
	data->shapes.light[i]->color = col_to_01(get_couple(values[3]));
	i++;
}

void	set_img(t_data *data, int *check)
{
	int	i;

	i = 0;
	if (data->shapes.max_c)
		data->mlx.img = (t_img *)malloc(sizeof(t_img) * data->shapes.max_c);
	if (!data->mlx.img)
	{
		error("KO! Malloc error", check, 0);
		return ;
	}
	while (i < data->shapes.max_c)
	{
		data->mlx.img[i].check = 0;
		data->mlx.img[i].img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGH);
		data->mlx.img[i].add = (int *)mlx_get_data_addr(data->mlx.img[i].img,
				&data->mlx.img[i].bpp, &data->mlx.img[i].w,
				&data->mlx.img[i].endian);
		i++;
	}
	i = 0;
}
