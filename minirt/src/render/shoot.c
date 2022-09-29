/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:25:59 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 15:40:30 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	shoot(t_data *data)
{
	t_intersect	in;
	t_ray		ray;

	ray = set_ray(data->shapes.cam[0]->origin, data->shapes.cam[0]->direction);
	in = launch_intersect(&ray, &data->shapes, 0);
	if (in.t != 0)
	{
		if (in.cilinder != NULL)
			data->shapes.potential1.cilinder_p[in.cilinder->id].called = 0;
		if (in.cone != NULL)
			data->shapes.potential1.cone_p[in.cone->id].called = 0;
		if (in.plane != NULL)
			data->shapes.potential1.plane_p[in.plane->id].called = 0;
		if (in.sphere != NULL)
		{
			data->shapes.potential1.sphere_p[in.sphere->id].called = 0;
		}
	}
}
