/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_get_dis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:42:41 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:28:19 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	get_dis_s(t_sphere *sphere, t_couple point)
{
	t_couple	temp;

	temp = c_res(point, sphere->origin);
	return (len(temp) - sphere->radious);
}

double	get_dis_p(t_plane *plane, t_couple point)
{
	double		dis;

	dis = ft_abs(dot(c_res(plane->origin, point), plane->normal));
	return (dis);
}

double	get_dis_cy(t_cilinder *cilinder, t_couple point)
{
	double		dis;
	t_couple	temp;

	temp = c_res(cilinder->origin, point);
	dis = len(temp) - sqrt((cilinder->height * cilinder->height)
			+ (cilinder->radious * cilinder->radious));
	return (dis);
}

double	get_dis_cn( t_cone *cone, t_couple point)
{
	t_couple	cam_vec;
	t_couple	axis;
	t_couple	tangent;
	t_couple	edge;

	cam_vec = normalized(c_res(point, cone->origin));
	axis = normalized(cross(cam_vec, cone->normal));
	tangent = normalized(cross(cone->normal, axis));
	edge = normalized(c_sum(tangent, cone->normal));
	return (sin(acos(dot(edge, cam_vec)))
		* len(c_res(point, cone->origin)));
}
