/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:25:18 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:32:01 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	launch_in_s(t_intersect *in, t_ray *ray, t_shapes *elem, int boo)
{
	int	i;

	i = 0;
	while (i < elem->max_s)
	{
		if (check_launch(in->t, elem->potential1.sphere_p[i].dis,
				elem->potential1.sphere_p[i].called, boo))
			in_sphere(in, trans_ray(ray,
					elem->sphere[i]->translate, NULL),
				elem->sphere[i], *ray);
		i++;
	}
}

void	launch_in_p(t_intersect *in, t_ray *ray, t_shapes *elem, int boo)
{
	int	i;

	i = 0;
	while (i < elem->max_p)
	{
		if (check_launch(in->t, elem->potential1.plane_p[i].dis,
				elem->potential1.plane_p[i].called, boo))
			in_plane(in, set_ray(ray->origin, ray->direction),
				elem->plane[i]);
		i++;
	}
}

void	launch_in_cy(t_intersect *in, t_ray *ray, t_shapes *elem, int boo)
{
	int	i;

	i = 0;
	while (i < elem->max_cy)
	{
		if (check_launch(in->t, elem->potential1.cilinder_p[i].dis,
				elem->potential1.cilinder_p[i].called, boo))
			in_cil(in, trans_ray(ray,
					elem->cilinder[i]->translate, &elem->cilinder[i]->rotate),
				elem->cilinder[i], *ray);
		i++;
	}
}

void	launch_in_cn(t_intersect *in, t_ray *ray, t_shapes *elem, int boo)
{
	int	i;

	i = 0;
	while (i < elem->max_cn)
	{
		if (check_launch(in->t, elem->potential1.cone_p[i].dis,
				elem->potential1.cone_p[i].called, boo))
			in_cone(in, trans_ray(ray,
					elem->cone[i]->translate, &elem->cone[i]->rotate),
				elem->cone[i], *ray);
		i++;
	}
}
