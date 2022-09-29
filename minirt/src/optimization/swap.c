/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:51:37 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:30:42 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	swap_sp(t_sphere **sp, t_called *called, int i)
{
	t_called	temp;
	t_sphere	*sp_temp;
	int			id;

	if (called[i].dis > called[i + 1].dis)
	{
		temp = called[i];
		called[i] = called[i + 1];
		called[i + 1] = temp;
		id = sp[i]->id;
		sp[i]->id = sp[i + 1]->id;
		sp[i + 1]->id = id;
		sp_temp = sp[i];
		sp[i] = sp[i + 1];
		sp[i + 1] = sp_temp;
	}
}

void	swap_plane(t_plane **plane, t_called *called, int i)
{
	t_called	temp;
	t_plane		*plane_temp;
	int			id;

	if (called[i].dis > called[i + 1].dis)
	{
		temp = called[i];
		called[i] = called[i + 1];
		called[i + 1] = temp;
		id = plane[i]->id;
		plane[i]->id = plane[i + 1]->id;
		plane[i + 1]->id = id;
		plane_temp = plane[i];
		plane[i] = plane[i + 1];
		plane[i + 1] = plane_temp;
	}
}

void	swap_cy(t_cilinder **cil, t_called *called, int i)
{
	t_called	temp;
	t_cilinder	*cil_temp;
	int			id;

	if (called[i].dis > called[i + 1].dis)
	{
		temp = called[i];
		called[i] = called[i + 1];
		called[i + 1] = temp;
		id = cil[i]->id;
		cil[i]->id = cil[i + 1]->id;
		cil[i + 1]->id = id;
		cil_temp = cil[i];
		cil[i] = cil[i + 1];
		cil[i + 1] = cil_temp;
	}
}

void	swap_cone(t_cone **cone, t_called *called, int i)
{
	t_called	temp;
	t_cone		*cone_temp;
	int			id;

	if (called[i].dis > called[i + 1].dis)
	{
		temp = called[i];
		called[i] = called[i + 1];
		called[i + 1] = temp;
		id = cone[i]->id;
		cone[i]->id = cone[i + 1]->id;
		cone[i + 1]->id = id;
		cone_temp = cone[i];
		cone[i] = cone[i + 1];
		cone[i + 1] = cone_temp;
	}
}
