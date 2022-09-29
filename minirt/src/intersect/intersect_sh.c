/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:12:58 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 19:54:30 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	in_plane_sh(t_ray ray, t_plane *plane, double dis)
{
	double	t;

	t = dot(ray.direction, plane->normal);
	if (t != 0)
	{
		t = dot(c_res(plane->origin, ray.origin), plane->normal) / t;
		if (t > 0 && t < dis)
		{
			return (1);
		}
	}
	return (0);
}

int	in_sphere_sh(t_ray ray, t_sphere *sphere, double dis)
{
	double	g1;
	double	g0;
	double	det;
	double	t;
	double	t2;

	g1 = 2.0 * dot(ray.direction, ray.origin);
	g0 = len2(ray.origin) - (sphere->radious * sphere->radious);
	det = g1 * g1 - (4.0 * 1 * g0);
	if (det == 0)
	{
		t = (-1 * g1) / (1 * 2.0);
		if (t > 0 && t < dis)
			return (1);
	}
	else if (det > 0)
	{
		t = ((-1) * g1 + (sqrt(det))) / (1 * 2.0);
		t2 = ((-1) * g1 - (sqrt(det))) / (1 * 2.0);
		if ((t > 0 || t2 > 0) && t < dis)
			return (1);
	}
	return (0);
}

int	in_disc_sh(t_disc disc, t_ray orig, double dis)
{
	double	t;
	double	ang;

	ang = dot(orig.direction, disc.normal);
	if (ang != 0)
	{
		t = dot(c_res(disc.origin, orig.origin), disc.normal) / ang;
		orig.t = t;
		if (t > 0 && t < dis
			&& inside_disc(disc.radious, set_point(orig.origin,
					orig.direction, orig.t), disc.origin))
			return (1);
	}
	return (0);
}

int	in_cil_sh(t_ray ray, t_cilinder *cil, t_ray orig, double dis)
{
	t_couple	grades;
	double		det;
	double		temp_t;
	double		t;
	double		h;

	if (in_disc_sh(cil->disc1, orig, dis)
		|| in_disc_sh(cil->disc2, orig, dis))
		return (1);
	det = get_det_c(&grades, cil->radious, ray);
	if (det == 0)
		t = (-1 * grades.y) / (grades.x * 2.0);
	else if (det > 0)
	{
		t = ((-1 * grades.y) + sqrt(det)) / (grades.x * 2.0);
		temp_t = ((-1 * grades.y) - sqrt(det)) / (grades.x * 2.0);
		if (temp_t > 0 && temp_t < t)
			t = temp_t;
	}
	else
		return (0);
	h = ray.direction.z * t + ray.origin.z;
	if (t > 0 && t < dis && h < cil->height && h > 0)
		return (1);
	return (0);
}

int	in_cone_sh(t_ray ray, t_cone *cone, t_ray orig, double dis)
{
	t_couple	grades;
	double		det;
	double		temp_t;
	double		t;

	(void)cone;
	(void)orig;
	det = get_det_cn(&grades, ray);
	if (det == 0)
		t = (-1 * grades.y) / (grades.x * 2.0);
	else if (det > 0)
	{
		t = ((-1 * grades.y) + sqrt(det)) / (grades.x * 2.0);
		temp_t = ((-1 * grades.y) - sqrt(det)) / (grades.x * 2.0);
		if ((temp_t < t && temp_t > 0) || (temp_t > 0 && t < 0))
			t = temp_t;
	}
	else
		return (0);
	if (t > 0 && t < dis)
		return (1);
	return (0);
}
