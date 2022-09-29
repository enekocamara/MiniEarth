/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersect_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:31:55 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 20:19:50 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	get_in_s(t_intersect *in, t_sphere *sph, t_couple nor, t_ray orig)
{
	in->t = orig.t;
	in->sphere = sph;
	in->cilinder = NULL;
	in->plane = NULL;
	in->cone = NULL;
	in->ray = orig;
	in->normal = nor;
}

void	get_in_c(t_intersect *in, t_cilinder *cil, t_ray orig, t_ray ray)
{
	double	h;

	h = ray.direction.z * orig.t + ray.origin.z;
	if (h < 0 || h > cil->height)
		return ;
	in->t = orig.t;
	in->plane = NULL;
	in->sphere = NULL;
	in->cone = NULL;
	in->cilinder = cil;
	in->normal = normalized(c_res(set_point(orig.origin, orig.direction,
					orig.t), set_point(cil->origin, cil->normal, h)));
	in->ray = orig;
}

void	get_in_pl(t_intersect *intersect, t_plane *plane, t_ray ray)
{
	intersect->t = ray.t;
	intersect->sphere = NULL;
	intersect->cilinder = NULL;
	intersect->cone = NULL;
	intersect->plane = plane;
	intersect->ray.direction = ray.direction;
	intersect->ray.origin = ray.origin;
	if (dot(plane->normal, ray.direction) > 0)
		intersect->normal = c_mul(plane->normal, -1);
	else
		intersect->normal = plane->normal;
}

void	get_disc(t_intersect *in, t_disc disc, t_ray orig)
{
	in->cilinder = NULL;
	in->sphere = NULL;
	in->plane = NULL;
	in->cone = NULL;
	in->t = orig.t;
	in->normal = disc.normal;
	in->ray = orig;
}

void	get_in_cn(t_intersect *in, t_cone *cone, t_ray orig, t_ray ray)
{
	double		h;
	t_couple	p;
	double		h2;

	h = ray.direction.z * orig.t + ray.origin.z;
	p = point(0, 0, h);
	in->t = orig.t;
	in->plane = NULL;
	in->sphere = NULL;
	in->cone = cone;
	in->cilinder = NULL;
	(void)ray;
	p = set_point(orig.origin, orig.direction, in->t);
	h2 = h + len(c_res(p, c_mul(cone->normal, h))) * TAN45;
	in->normal = normalized(c_res(p, c_sum(c_mul(cone->normal, h2),
					cone->origin)));
	in->ray = set_ray(orig.origin, orig.direction);
}
