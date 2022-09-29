/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:08:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 14:03:54 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	init_intersect(t_intersect *intersect)
{
	intersect->cilinder = NULL;
	intersect->sphere = NULL;
	intersect->plane = NULL;
	intersect->cone = NULL;
	intersect->t = 0;
	intersect->normal = vector(0, 0, 0);
}

int	check_launch(double t, double dis, int called, int boo)
{
	//return (1);
	if (!called)
		return (0);
	if (boo)
	{
		if (dis < t || t == 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

t_intersect	launch_intersect(t_ray *ray, t_shapes *elements, int times)
{
	t_intersect	intersect;
	int			boo;

	boo = 0;
	if (times == 0)
		boo = 1;
	init_intersect(&intersect);
	launch_in_s(&intersect, ray, elements, boo);
	launch_in_p(&intersect, ray, elements, boo);
	launch_in_cy(&intersect, ray, elements, boo);
	launch_in_cn(&intersect, ray, elements, boo);
	return (intersect);
}

int	launch_shadow(t_ray ray, t_shapes *elements, double dis)
{
	if (!launch_shadow_p(ray, elements, dis))
		return (0);
	if (!launch_shadow_s(ray, elements, dis))
		return (0);
	if (!launch_shadow_cy(ray, elements, dis))
		return (0);
	if (!launch_shadow_cn(ray, elements, dis))
		return (0);
	return (1);
}
