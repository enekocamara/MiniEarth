/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:15:49 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/27 12:38:24 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../mlx/mlx.h"

void	launch_in_skybox(t_intersect *in, t_ray ray, t_shapes *elem)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		in_plane(in, set_ray(ray.origin, ray.direction),
			&elem->skybox->plane[i]);
		i++;
	}
}

t_couple	int_to_col01(int temp)
{
	t_couple	col;

	col.x = (temp >> 16) & 0xFF;
	col.y = (temp >> 8) & 0xFF;
	col.z = temp & 0xFF;
	return (col);
}

int	convert(int a, int b, int mode)
{
	int	index;

	index = 20;
	if (mode == 0)
		return (clamp(0, SKBW * SKBH, a * SKBW
				+ clamp(index, SKBD - index, b) + SKBD));
	if (mode == 1)
		return (clamp(0, SKBW * SKBH, (a + SKBD * 2) * SKBW
				+ clamp(index, SKBD - index, b) + SKBD));
	if (mode == 2)
		return (clamp(0, SKBW * SKBH, (clamp(index, SKBD - index, a)
					+ SKBD) * SKBW + b + SKBD));
	if (mode == 3)
		return (clamp(0, SKBW * SKBH, (clamp(index, SKBD - index, a) + SKBD)
				* SKBW + b + SKBD * 3));
	if (mode == 4)
		return (clamp(0, SKBW * SKBH, (clamp(index, SKBD - index, a) + SKBD)
				* SKBW + b + SKBD * 2));
	if (mode == 5)
		return (clamp(0, SKBW * SKBH, (clamp(index, SKBD - index, a) + SKBD)
				* SKBW + b));
	return (0);
}

int	get_skb_col(t_intersect *in, t_shapes *elem, t_couple point)
{
	if (in->plane->id == 0)
		return (elem->skybox->textures.add[
				convert(point.z + SKBD2, point.x + SKBD2, 0)]);
	else if (in->plane->id == 1)
		return (elem->skybox->textures.add[
				convert(-1 * point.z + SKBD2, point.x + SKBD2, 1)]);
	else if (in->plane->id == 2)
		return (elem->skybox->textures.add[
				convert(-1 * point.y + SKBD2, point.x + SKBD2, 2)]);
	else if (in->plane->id == 3)
		return (elem->skybox->textures.add[
				convert(-1 * point.y + SKBD2, -1 * point.x + SKBD2, 3)]);
	else if (in->plane->id == 4)
		return (elem->skybox->textures.add[
				convert(-1 * point.y + SKBD2, -1 * point.z + SKBD2, 4)]);
	else if (in->plane->id == 5)
		return (elem->skybox->textures.add[
				convert(-1 * point.y + SKBD2, point.z + SKBD2, 5)]);
	else
		return (0);
}

t_couple	skybox(t_shapes *elem, t_ray ray)
{
	int			temp_col;
	t_couple	point;
	t_intersect	in;

	init_intersect(&in);
	launch_in_skybox(&in, ray, elem);
	point = get_point(in, 0);
	temp_col = get_skb_col(&in, elem, point);
	return (col_to_01(int_to_col01(temp_col)));
}
