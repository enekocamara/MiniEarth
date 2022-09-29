/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:39:13 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/21 20:19:31 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	get_potential(t_shapes	*elements)
{
	if (elements->max_s)
		elements->potential1.sphere_p
			= (t_called *)malloc(sizeof(t_called) * elements->max_s);
	if (elements->max_p)
		elements->potential1.plane_p
			= (t_called *)malloc(sizeof(t_called) * elements->max_p);
	if (elements->max_cy)
		elements->potential1.cilinder_p
			= (t_called *)malloc(sizeof(t_called) * elements->max_cy);
	if (elements->max_cn)
		elements->potential1.cone_p
			= (t_called *)malloc(sizeof(t_called) * elements->max_cn);
}

void	init_called(t_shapes *elem)
{
	int	i;

	i = -1;
	while (++i < elem->max_s)
		elem->potential1.sphere_p[i].called = 1;
	i = -1;
	while (++i < elem->max_p)
		elem->potential1.plane_p[i].called = 1;
	i = -1;
	while (++i < elem->max_cy)
		elem->potential1.cilinder_p[i].called = 1;
	i = -1;
	while (++i < elem->max_cn)
		elem->potential1.cone_p[i].called = 1;
}

void	set_potential(t_shapes *elem, t_couple point)
{
	int	i;

	i = -1;
	while (++i < elem->max_s)
		elem->potential1.sphere_p[i].dis = get_dis_s(elem->sphere[i], point);
	if (elem->max_s)
		order(elem, elem->potential1.sphere_p, elem->max_s, 1);
	i = -1;
	while (++i < elem->max_p)
		elem->potential1.plane_p[i].dis = get_dis_p(elem->plane[i], point);
	if (elem->max_p)
		order(elem, elem->potential1.plane_p, elem->max_p, 2);
	i = -1;
	while (++i < elem->max_cy)
		elem->potential1.cilinder_p[i].dis
			= get_dis_cy(elem->cilinder[i], point);
	if (elem->max_cy)
		order(elem, elem->potential1.cilinder_p, elem->max_cy, 3);
	i = -1;
	while (++i < elem->max_cn)
		elem->potential1.cone_p[i].dis
			= get_dis_cn(elem->cone[i], point);
	if (elem->max_cn)
		order(elem, elem->potential1.cone_p, elem->max_cn, 4);
}

void	order(t_shapes *elem, t_called *potential1, int max, int check)
{
	int	i;
	int	j;

	j = 0;
	while (j < max)
	{
		i = 0;
		while (i < max - 1)
		{
			if (check == 1)
				swap_sp(elem->sphere, potential1, i);
			if (check == 2)
				swap_plane(elem->plane, potential1, i);
			if (check == 3)
				swap_cy(elem->cilinder, potential1, i);
			if (check == 4)
				swap_cone(elem->cone, potential1, i);
			i++;
		}
		j++;
	}
}
