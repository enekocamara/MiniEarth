/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:40:10 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/29 14:44:43 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	key_hook(int keycode, t_data *data)
{
	/*if (keycode == 124 && data->mlx.img_index < data->shapes.max_c - 1)
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
			data->mlx.img[++data->mlx.img_index].img, 0, 0);
	if (keycode == 123 && data->mlx.img_index > 0)
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
			data->mlx.img[--data->mlx.img_index].img, 0, 0);*/
	(void)data;
	if (keycode == 53)
		exit (0);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(c_mul(data->shapes.cam[0]->right, -1), 0.1),
					data->shapes.cam[0]->direction));
	else if (keycode == 2)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(data->shapes.cam[0]->right, 0.1),
					data->shapes.cam[0]->direction));
	else if (keycode == 4)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(c_mul(data->shapes.cam[0]->up, -1), 0.1),
					data->shapes.cam[0]->direction));
	else if (keycode == 5)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(data->shapes.cam[0]->up, 0.1),
					data->shapes.cam[0]->direction));
	else if (keycode == 3)
		shoot(data);
	else
		return (0);
	set_axis_cam(data, 0);
	render(data);
	return (0);
}

void	free_data(t_data *data)
{
	free_input(data);
	free(data->mlx.img);
	free(data->shapes.potential1.cilinder_p);
	free(data->shapes.potential1.sphere_p);
	free(data->shapes.potential1.plane_p);
}

int	ft_eventspress(int keycode, t_data *data)
{
	if (keycode == 13)
		data->f = 1;
	else if (keycode == 1)
		data->b = 1;
	else if (keycode == 2)
		data->r = 1;
	else if (keycode == 0)
		data->l = 1;
	else if (keycode == 257)
		data->d = 1;
	else if (keycode == 49)
		data->u = 1;
	else if (keycode == 49)
		data->u = 1;
	else if (keycode == 123)
		data->ll = 1;
	else if (keycode == 124)
		data->lr = 1;
	else if (keycode == 125)
		data->ld = 1;
	else if (keycode == 126)
		data->lu = 1;
	else if (keycode == 36)
		printf("[%lf,%lf,%lf][%lf,%lf,%lf]\n", data->shapes.cam[0]->origin.x, data->shapes.cam[0]->origin.y, data->shapes.cam[0]->origin.z, data->shapes.cam[0]->direction.x, data->shapes.cam[0]->direction.y, data->shapes.cam[0]->direction.z);
	else
		return (0);
	//render(data);
	return (0);
}

int	ft_eventsrealese(int keycode, t_data *data)
{
	if (keycode == 13)
		data->f = 0;
	else if (keycode == 1)
		data->b = 0;
	else if (keycode == 2)
		data->r = 0;
	else if (keycode == 0)
		data->l = 0;
	else if (keycode == 257)
		data->d = 0;
	else if (keycode == 49)
		data->u = 0;
	else if (keycode == 123)
		data->ll = 0;
	else if (keycode == 124)
		data->lr = 0;
	else if (keycode == 125)
		data->ld = 0;
	else if (keycode == 126)
		data->lu = 0;
	return (0);
}


int showframes(t_data *data)
{

	if (data->f)
		data->shapes.cam[0]->origin = c_sum(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->direction);
	if (data->b)
		data->shapes.cam[0]->origin = c_res(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->direction);
	if (data->r)
		data->shapes.cam[0]->origin = c_sum(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->right);
	if (data->l)
		data->shapes.cam[0]->origin = c_res(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->right);
	if (data->d)
		data->shapes.cam[0]->origin = c_res(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->up);
	if (data->u)
		data->shapes.cam[0]->origin = c_sum(data->shapes.cam[0]->origin,
				data->shapes.cam[0]->up);
	if (data->ll)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(c_mul(data->shapes.cam[0]->right, -1), 0.05),
					data->shapes.cam[0]->direction));
	if (data->lr)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(data->shapes.cam[0]->right, 0.05),
					data->shapes.cam[0]->direction));
	if (data->ld)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(c_mul(data->shapes.cam[0]->up, -1), 0.05),
					data->shapes.cam[0]->direction));
	if (data->lu)
		data->shapes.cam[0]->direction = normalized(c_sum(
					c_mul(data->shapes.cam[0]->up, 0.05),
					data->shapes.cam[0]->direction));
	if (data->ll || data->ld || data->lu || data->lr)
		set_axis_cam(data, 0);
	data->shapes.earth->index += 20;
	/*int	i;

	i = 0;
	while (i < data->shapes.max_s)
	{
		data->shapes.sphere[i]->origin.y -= 1;
		data->shapes.sphere[i]->translate->matrix[1][3] += 1;
		i++;
	}*/
	render(data);
	return (0);
	render(data);
	return (0);
}


int	main(int argc, char *argv[])
{
	t_data			data;
	struct timeval	now;
	struct timeval	later;

	g_ids = 0;
	gettimeofday(&now, NULL);
	data.f = 0;
	data.b = 0;
	data.l = 0;
	data.r = 0;
	data.u = 0;
	data.d = 0;
	data.ll = 0;
	data.lr = 0;
	data.lu = 0;
	data.ld = 0;
	if (argc != 2)
		return (1);
	set_data(&data, argv);
	gettimeofday(&later, NULL);
	printf(KBLU"Data allocated [%lf sec]\n",
		(ft_to_sec(later) - ft_to_sec(now)));
	render(&data);
	gettimeofday(&now, NULL);
	printf(KGRN"\nTime to render[%lf sec]\n\n"KBLU,
		ft_to_sec(now) - ft_to_sec(later));
	mlx_key_hook(data.mlx.win, key_hook, &data);
	mlx_hook(data.mlx.win, 17, 1L << 5, ft_close, &data);
	mlx_mouse_hook(data.mlx.win, mouse_hook, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, ft_eventspress, &data);
	mlx_hook(data.mlx.win, 3, 1L << 0, ft_eventsrealese, &data);
	mlx_loop_hook(data.mlx.mlx, showframes, &data);
	mlx_loop(data.mlx.mlx);
	//free_data(&data);
	return (0);
}
