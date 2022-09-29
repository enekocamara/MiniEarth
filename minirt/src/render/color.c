/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:58:09 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:33:50 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	convert_color(t_couple col)
{
	col = gamm_correction(col);
	col = col_to_255(col);
	return (convert_rgb(col));
}

int	check_if_ref(t_intersect intersect)
{
	if (intersect.sphere && intersect.sphere->ref)
		return (1);
	if (intersect.plane && intersect.plane->ref)
		return (1);
	if (intersect.cilinder && intersect.cilinder->ref)
		return (1);
	if (intersect.cone && intersect.cone->ref)
		return (1);
	return (0);
}

double	all_ref(t_intersect intersect)
{
	if (intersect.sphere)
		return (intersect.sphere->ref);
	if (intersect.plane)
		return (intersect.plane->ref);
	if (intersect.cilinder)
		return (intersect.cilinder->ref);
	if (intersect.cone)
		return (intersect.cone->ref);
	return (0);
}

t_couple	color(t_ray ray, t_shapes *elements, int times, double old_ref)
{
	t_intersect	intersect;
	t_couple	temp_col;
	t_couple	col;
	double		ref;

	temp_col = vector(0, 0, 0);
	col = vector(0, 0, 0);
	while (times++ <= RAY_DEPTH)
	{
		intersect = launch_intersect(&ray, elements, times);
		if (intersect.t == 0 && elements->skybox->active)
			return (c_clamp(0, 1, c_sum(c_mul(skybox(elements, ray),
							old_ref), col)));
		ref = all_ref(intersect);
		if (ref != 1 || times == RAY_DEPTH)
			temp_col = get_col(&intersect, elements);
		if (ref == 0 || times == RAY_DEPTH)
			return (c_clamp(0, 1, c_sum(c_mul(temp_col, old_ref), col)));
		else
			col = c_clamp(0, 1, c_sum(c_sum(c_mul(temp_col,
								(1 - ref) * old_ref), col), col));
		ray = set_ray(get_point(intersect, 1), all_rebound(intersect));
		old_ref = ref;
	}
	return (col);
}

t_couple	get_col(t_intersect *intersect, t_shapes *elements)
{
	t_couple	temp_col;

	temp_col = vector(0, 0, 0);
	if (intersect->sphere != NULL)
	{
		temp_col = lighting_s(intersect, elements, temp_col);
		return (temp_col);
	}
	if (intersect->plane != NULL)
	{
		temp_col = lighting_p(intersect, elements, temp_col);
		return (temp_col);
	}
	if (intersect->cilinder != NULL)
	{
		temp_col = lighting_c(intersect, elements, temp_col);
		return (temp_col);
	}
	if (intersect->cone != NULL)
	{
		temp_col = lighting_cn(intersect, elements, temp_col);
		return (temp_col);
	}
	return (temp_col);
}
