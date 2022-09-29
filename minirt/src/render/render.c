/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:55:49 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/27 14:32:45 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_couple	get_direction(double i, double j, t_cam *cam)
{
	t_couple	new;
	t_couple	up;
	t_couple	right;

	up = c_mul(cam->up, j * cam->h);
	right = c_mul(cam->right, i * cam->w);
	new = normalized(c_sum(c_sum(cam->direction, up), right));
	return (new);
}

int	ray_trace(t_data *data, double i, double j, t_cam *cam)
{
	t_ray		ray;

	i = ((((i + 0.5) / WIDTH) * 2) - 1);
	j = (-2 * j) / HEIGH + 1;
	ray.direction = get_direction(i, j, cam);
	ray.origin = cam->origin;
	return (convert_color(color(ray, &data->shapes, 0, 1)));
}

void	*render2(void *temp)
{
	int	render;
	int	i;
	int	j;
	int	temp_id;

	temp_id = g_ids;
	g_ids++;
	render = 0;
	t_data *data = temp;
	while (render < data->shapes.max_c)
	{
		data->shapes.render = render;
		if (temp_id == 0)
		{
			set_potential(&data->shapes, data->shapes.cam[render]->origin);
			data->id = 1;
		}
		while(data->id == 0)
			continue ;
		j = -1;
		//printf("...\n");
		while (++j < HEIGH)
		{
			i = temp_id;
			while (i < WIDTH)
			{
				data->mlx.img[render].add[(j * WIDTH) + i]
					= ray_trace(data, i, j, data->shapes.cam[render]);
				i += THREADS;
				/*if (temp_id == 0)
					printf("[%d]\n", i);*/
			}
		}
		data->mlx.img[render].add[((HEIGH / 2) * WIDTH) + WIDTH / 2]
					= convert_color(vector(1, 0, 0));
		render++;
		//printf(KBLU"\nFrame Nº%d rendered.\n", render);
	}
	return (NULL);
}

void	render(t_data *data)
{
	int	i;

	i = 0;
	data->id = 0;
	while (i < THREADS)
	{
		//pthread_mutex_lock(data->thread.mutex);
		if (pthread_create(&data->mutex[i], NULL, &render2,
				data) != 0)
			return ;
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(data->mutex[i], NULL);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.win, data->mlx.img[0].img, 0, 0);
	g_ids = 0;
}
/*
	render = 0;
	while (render < data->shapes.max_c)
	{
		data->shapes.render = render;
		set_potential(&data->shapes, data->shapes.cam[render].origin);
		j = -1;
		printf("...\n");
		while (++j < HEIGH)
		{
			i = -1;
			while (++i < WIDTH)
			{
				data->mlx.img[render].add[(j * WIDTH) + i]
					= ray_trace(data, i, j, data->shapes.cam[render]);
			}
		}
		render++;
		printf(KBLU"\nFrame Nº%d rendered.\n", render);
	}
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.win, data->mlx.img[0].img, 0, 0);
}
*/