/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_shadow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:28:39 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:33:07 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	launch_shadow_p(t_ray ray, t_shapes *elements, double dis)
{
	int	i;

	i = 0;
	while (i < elements->max_p)
	{
		if (elements->potential1.plane_p[i].called
			&& in_plane_sh(ray, elements->plane[i], dis))
			return (0);
		i++;
	}
	return (1);
}

int	launch_shadow_s(t_ray ray, t_shapes *elements, double dis)
{
	int	i;

	i = 0;
	while (i < elements->max_s)
	{
		if (elements->potential1.sphere_p[i].called
			&& in_sphere_sh(trans_ray(&ray,
					elements->sphere[i]->translate, NULL),
				elements->sphere[i], dis))
			return (0);
		i++;
	}
	return (1);
}

int	launch_shadow_cy(t_ray ray, t_shapes *elements, double dis)
{
	int	i;

	i = 0;
	while (i < elements->max_cy)
	{
		if (elements->potential1.cilinder_p[i].called
			&& in_cil_sh(trans_ray(&ray,
					elements->cilinder[i]->translate,
					&elements->cilinder[i]->rotate),
				elements->cilinder[i], ray, dis))
			return (0);
		i++;
	}
	return (1);
}

int	launch_shadow_cn(t_ray ray, t_shapes *elements, double dis)
{
	int	i;

	i = 0;
	while (i < elements->max_cn)
	{
		if (elements->potential1.cone_p[i].called
			&& in_cone_sh(trans_ray(&ray,
					elements->cone[i]->translate,
					&elements->cone[i]->rotate),
				elements->cone[i], ray, dis))
			return (0);
		i++;
	}
	return (1);
}
