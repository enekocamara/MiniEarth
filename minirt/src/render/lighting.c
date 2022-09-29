/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:15:00 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/29 16:24:31 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_couple	lighting_earth(t_intersect *in, t_shapes *elem, t_couple col)
{
	t_couple	point;
	t_couple	light;
	double		f;
	//t_couple	temp_col;
	t_couple	col_day;
	t_couple	col_night;
	t_couple	clouds;
	int			i;

	point = get_point(*in, 1);
	i = -1;
	col_day = get_color_sphere(elem, translate(get_point(*in, 0), in->sphere->translate), elem->earth->day);
	col_night = get_color_sphere(elem, translate(get_point(*in, 0), in->sphere->translate), elem->earth->night);
	clouds = get_color_sphere(elem, translate(get_point(*in, 0), in->sphere->translate), elem->earth->clouds);
	while (++i < elem->max_l)
	{
		light = elem->light[i]->origin;
		f = dot(normalized(c_res(light, point)), in->normal);
		f += pow(clamp(0, 1, dot(normalized(rebound(normalized (c_res(point,
										light)), in->normal)),
						c_mul(in->ray.direction, -1))), PONG) * PONGONOFF;
		f *= elem->light[i]->range;
		f *= launch_shadow(set_ray(point, normalized(c_res(light, point))),
				elem, len(c_res(light, point)));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(col_day, elem->light[i]->color),
						f - len(clouds)), col));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(vector(1,1,1), elem->light[i]->color),
						f * len(clouds)), col));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(col_night, elem->light[i]->color),
						pow(1 - f, 5)), col));
	}
	col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(col_day,
						elem->ambient_l->color), elem->ambient_l->range), col));
	return (col);
}

t_couple	lighting_s(t_intersect *in, t_shapes *elem, t_couple col)
{
	t_couple	point;
	t_couple	light;
	double		f;
	t_couple	temp_col;
	int			i;

	point = get_point(*in, 1);
	i = -1;
	temp_col = in->sphere->color;
	if (1)
		return (lighting_earth(in, elem, col));
	while (++i < elem->max_l)
	{
		light = elem->light[i]->origin;
		f = dot(normalized(c_res(light, point)), in->normal);
		f += pow(clamp(0, 1, dot(normalized(rebound(normalized (c_res(point,
										light)), in->normal)),
						c_mul(in->ray.direction, -1))), PONG) * PONGONOFF;
		f *= elem->light[i]->range;
		f *= launch_shadow(set_ray(point, normalized(c_res(light, point))),
				elem, len(c_res(light, point)));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(temp_col, elem->light[i]->color),
						f), col));
	}
	col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(temp_col,
						elem->ambient_l->color), elem->ambient_l->range), col));
	return (col);
}

t_couple	lighting_p(t_intersect *in, t_shapes *elem, t_couple col)
{
	t_couple	point;
	t_light		*light;
	double		f;
	int			i;

	i = -1;
	point = get_point(*in, 1);
	while (++i < elem->max_l)
	{
		light = elem->light[i];
		f = dot(in->normal, normalized(c_res(light->origin, point)));
		f += pow(clamp(0, 1, dot(normalized(rebound(normalized(c_res(point,
										light->origin)), in->normal)),
						c_mul(in->ray.direction, -1))), PONG) * PONGONOFF;
		f *= light->range;
		f *= launch_shadow(set_ray(point, normalized(c_res(light->origin,
							point))), elem, len(c_res(light->origin, point)));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->plane->color,
							elem->light[i]->color), f), col));
	}
	col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->plane->color,
						elem->ambient_l->color), elem->ambient_l->range), col));
	return (col);
}

t_couple	lighting_c(t_intersect *in, t_shapes *elem, t_couple col)
{
	int			i;
	double		f;
	t_couple	point;
	t_light		*light;

	i = 0;
	point = get_point(*in, 1);
	while (i < elem->max_l)
	{
		light = elem->light[i];
		f = dot(in->normal, normalized(c_res(light->origin, point)));
		f += pow(clamp(0, 1, dot(normalized(rebound(normalized(c_res(point,
										light->origin)), in->normal)),
						c_mul(in->ray.direction, -1))), PONG) * PONGONOFF;
		f *= launch_shadow(set_ray(point, normalized(c_res(light->origin,
							point))), elem, len(c_res(light->origin, point)));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->cilinder->color,
							light->color), f), col));
		i++;
	}
	col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->cilinder->color,
						elem->ambient_l->color), elem->ambient_l->range), col));
	return (col);
}

t_couple	lighting_cn(t_intersect *in, t_shapes *elem, t_couple col)
{
	int			i;
	double		f;
	t_couple	point;
	t_light		*light;

	i = 0;
	point = get_point(*in, 1);
	while (i < elem->max_l)
	{
		light = elem->light[i];
		f = dot(in->normal, normalized(c_res(light->origin, point)));
		f += pow(clamp(0, 1, dot(normalized(rebound(normalized(c_res(point,
										light->origin)), in->normal)),
						c_mul(in->ray.direction, -1))), PONG) * PONGONOFF;
		f *= launch_shadow(set_ray(point, normalized(c_res(light->origin,
							point))), elem, len(c_res(light->origin, point)));
		col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->cone->color,
							light->color), f), col));
		i++;
	}
	col = c_clamp(0, 1, c_sum(c_mul(c_mul_c(in->cone->color,
						elem->ambient_l->color), elem->ambient_l->range), col));
	return (col);
}
