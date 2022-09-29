/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:12:19 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/28 17:03:02 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	create_skb_img(t_data *data)
{
	int	x;
	int	y;

	x = SKBW;
	y = SKBH;
	data->shapes.skybox->textures.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"src/skybox/texture/skyboxHD.xpm", &x, &y);
	data->shapes.skybox->textures.add = (int *)mlx_get_data_addr(
			data->shapes.skybox->textures.img,
			&data->shapes.skybox->textures.bpp, &data->shapes.skybox->textures.w,
			&data->shapes.skybox->textures.endian);
}

void	set_skybox(t_data *data)
{
	data->shapes.skybox->plane[0].origin = point(0, SKBD2, 0);
	data->shapes.skybox->plane[0].normal = point(0, -1, 0);
	data->shapes.skybox->plane[0].id = 0;
	data->shapes.skybox->plane[1].origin = point(0, -SKBD2, 0);
	data->shapes.skybox->plane[1].normal = point(0, 1, 0);
	data->shapes.skybox->plane[1].id = 1;
	data->shapes.skybox->plane[2].origin = point(0, 0, SKBD2);
	data->shapes.skybox->plane[2].normal = point(0, 0, -1);
	data->shapes.skybox->plane[2].id = 2;
	data->shapes.skybox->plane[3].origin = point(0, 0, -SKBD2);
	data->shapes.skybox->plane[3].normal = point(0, 0, 1);
	data->shapes.skybox->plane[3].id = 3;
	data->shapes.skybox->plane[4].origin = point(SKBD2, 0, 0);
	data->shapes.skybox->plane[4].normal = point(-1, 0, 0);
	data->shapes.skybox->plane[4].id = 4;
	data->shapes.skybox->plane[5].origin = point(-SKBD2, 0, 0);
	data->shapes.skybox->plane[5].normal = point(-1, 0, 0);
	data->shapes.skybox->plane[5].id = 5;
	create_skb_img(data);
}
