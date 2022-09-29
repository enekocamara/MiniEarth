/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebound.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:13:50 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/15 16:13:00 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_couple	rebound(t_couple ray, t_couple normal)
{
	return (c_sum(ray, c_mul(normal, -2 * dot(ray, normal))));
}

t_couple	all_rebound(t_intersect intersect)
{
	return (rebound(intersect.ray.direction, intersect.normal));
	if (intersect.sphere)
	{
		return (rebound(intersect.ray.direction, intersect.normal));
	}
	if (intersect.plane)
	{
		return (rebound(intersect.ray.direction, intersect.normal));
	}
	if (intersect.cilinder)
	{
		return (rebound(intersect.ray.direction, intersect.normal));
	}
	if (intersect.cone)
	{
		return (rebound(intersect.ray.direction, intersect.normal));
	}
	return (vector(0, 0, 0));
}
