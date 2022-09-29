/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_shapes_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:51:19 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/21 19:52:06 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	get_det_c(t_couple *grades, double radious, t_ray ray)
{
	grades->x = (ray.direction.x * ray.direction.x)
		+ (ray.direction.y * ray.direction.y);
	grades->y = 2 * ray.origin.x * ray.direction.x
		+ 2 * ray.origin.y * ray.direction.y;
	grades->z = (ray.origin.x * ray.origin.x)
		+ (ray.origin.y * ray.origin.y) - (radious * radious);
	return ((grades->y * grades->y) - (4 * grades->x * grades->z));
}

double	get_det_cn(t_couple *grades, t_ray ray)
{
	grades->x = ray.direction.x * ray.direction.x
		+ ray.direction.y * ray.direction.y
		- ray.direction.z * ray.direction.z;
	grades->y = (2 * ray.origin.x * ray.direction.x)
		+ (2 * ray.origin.y * ray.direction.y)
		- (2 * ray.origin.z * ray.direction.z);
	grades->z = (ray.origin.x * ray.origin.x)
		+ (ray.origin.y * ray.origin.y)
		- (ray.origin.z * ray.origin.z);
	return ((grades->y * grades->y) - (4 * grades->x * grades->z));
}

int	inside_disc(double radious, t_couple point, t_couple origin)
{
	double	dis;

	dis = len(c_res(point, origin));
	if (dis < radious)
		return (1);
	return (0);
}

t_couple	get_normal_c(t_cilinder *cil, t_ray ray)
{
	double		hypotenusa;
	double		t;
	t_couple	point;
	t_couple	proyection;

	point = set_point(ray.origin, ray.direction, ray.t);
	hypotenusa = len(c_res(point, cil->origin));
	t = cos(acos(dot(cil->normal, normalized(c_res(point, cil->origin)))));
	proyection = set_point(cil->origin, cil->normal, t);
	return (normalized(c_res(point, proyection)));
}

void	in_cone(t_intersect *in, t_ray ray, t_cone *cone, t_ray orig)
{
	t_couple	grades;
	double		det;
	double		temp_t;

	det = get_det_cn(&grades, ray);
	if (det == 0)
	{
		orig.t = (-grades.y) / (grades.x * 2.0);
		if ((orig.t < in->t || in->t == 0) && orig.t > 0)
			get_in_cn(in, cone, orig, ray);
	}
	else if (det > 0.0)
	{
		orig.t = ((-1.0 * grades.y) + sqrt(det)) / (grades.x * 2.0);
		temp_t = ((-1.0 * grades.y) - sqrt(det)) / (grades.x * 2.0);
		if (((orig.t < temp_t && orig.t > 0) || (orig.t > 0 && temp_t < 0))
			&& (orig.t < in->t || in->t == 0))
			get_in_cn(in, cone, orig, ray);
		else if (((temp_t < orig.t && temp_t > 0) || (temp_t > 0 && orig.t < 0))
			&& (temp_t < in->t || in->t == 0))
		{
			orig.t = temp_t;
			get_in_cn(in, cone, orig, ray);
		}
	}
}
