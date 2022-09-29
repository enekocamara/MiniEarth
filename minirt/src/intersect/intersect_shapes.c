/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:31:20 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/14 17:37:47 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	in_disc(t_intersect *in, t_ray ray, t_disc *disc, t_ray orig)
{
	double	t;
	double	angle;

	(void)ray;
	angle = dot(orig.direction, disc->normal);
	if (angle != 0)
	{
		t = dot(c_res(disc->origin, orig.origin), disc->normal) / angle;
		orig.t = t;
		if (t > 0 && (t < in->t || in->t == 0)
			&& inside_disc(disc->radious, set_point(orig.origin,
					orig.direction, orig.t), disc->origin))
		{
			get_disc(in, *disc, orig);
			return (1);
		}
	}
	return (0);
}

void	in_cil(t_intersect *in, t_ray ray, t_cilinder *cil, t_ray orig)
{
	t_couple	grades;
	double		det;
	double		temp_t;

	if (in_disc(in, ray, &cil->disc1, orig))
		in->cilinder = cil;
	if (in_disc(in, ray, &cil->disc2, orig))
		in->cilinder = cil;
	det = get_det_c(&grades, cil->radious, ray);
	if (det == 0)
	{
		orig.t = (-1 * grades.y) / (grades.x * 2.0);
		if ((orig.t < in->t || in->t == 0) && orig.t > 0)
			get_in_c(in, cil, orig, ray);
	}
	else if (det > 0)
	{
		orig.t = (-grades.y + sqrt(det)) / (grades.x * 2.0);
		temp_t = (-grades.y - sqrt(det)) / (grades.x * 2.0);
		if (orig.t > temp_t && temp_t > 0)
			orig.t = temp_t;
		if (orig.t > 0 && (orig.t < in->t || in->t == 0))
			get_in_c(in, cil, orig, ray);
	}
}

void	in_plane(t_intersect *intersect, t_ray ray, t_plane *plane)
{
	double	t;

	t = dot(ray.direction, plane->normal);
	if (t != 0)
	{
		t = dot(c_res(plane->origin, ray.origin), plane->normal) / t;
		if (t > 0 && (t < intersect->t || intersect->t == 0))
		{
			ray.t = t;
			get_in_pl(intersect, plane, ray);
		}
	}
}

double	sphere_answer(double det, double g1, t_couple *nor, t_ray ray)
{
	double	t;
	double	t2;
	double	ans;

	t = ((-1) * g1 + (sqrt(det))) / (2.0);
	t2 = ((-1) * g1 - (sqrt(det))) / (2.0);
	if ((t < t2 && t > 0) || (t2 < 0 && t > 0))
		ans = t;
	else if ((t2 < t && t2 > 0) || (t < 0 && t2 > 0))
		ans = t2;
	else
		return (-1);
	if ((t2 < 0 && t > 0) || (t < 0 && t2 > 0))
		*nor = c_mul(normalized(set_point(ray.origin, ray.direction, ans)), -1);
	else
		*nor = normalized(set_point(ray.origin, ray.direction, ans));
	return (ans);
}

void	in_sphere(t_intersect *in, t_ray ray, t_sphere *sph, t_ray orig)
{
	double		g1;
	double		g0;
	double		det;
	double		t;
	t_couple	nor;

	g1 = 2.0 * dot(ray.direction, ray.origin);
	g0 = len2(ray.origin) - (sph->radious * sph->radious);
	det = g1 * g1 - (4.0 * 1 * g0);
	if (det == 0)
	{
		t = (-1 * g1) / (1 * 2.0);
		orig.t = t;
		nor = set_point(ray.origin, ray.direction, t);
		if ((in->t == 0 || t < in->t) && t > 0)
			get_in_s(in, sph, nor, orig);
	}
	else if (det > 0)
	{
		t = sphere_answer(det, g1, &ray.direction, ray);
		orig.t = t;
		if (t > 0 && (t < in->t || in->t == 0))
			get_in_s(in, sph, ray.direction, orig);
	}
}
