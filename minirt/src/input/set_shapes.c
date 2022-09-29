/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:29:36 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/27 16:08:08 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	set_sphere(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_sphere	*temp;

	temp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!i)
		i = 0;
	data->shapes.sphere[i] = temp;
	values = ft_split(line, ' ');
	data->shapes.sphere[i]->origin = get_couple(values[1]);
	data->shapes.sphere[i]->radious = ft_atoi_double(values[2]);
	data->shapes.sphere[i]->color = col_to_01(get_couple(values[3]));
	data->shapes.sphere[i]->id = i;
	data->shapes.sphere[i]->translate = set_translation(point(0, 0, 0),
			c_mul(data->shapes.sphere[i]->origin, -1.0));
	data->shapes.sphere[i]->ref = 0;
	if (values[4])
		data->shapes.sphere[i]->ref = ft_atoi_double(values[4]);
	data->shapes.sphere[i]->id = i;
	i++;
}

void	set_plane(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_plane		*temp;

	temp = (t_plane *)malloc(sizeof(t_plane));
	if (!i)
		i = 0;
	values = ft_split(line, ' ');
	data->shapes.plane[i] = temp;
	data->shapes.plane[i]->origin = get_couple(values[1]);
	data->shapes.plane[i]->normal = normalized(get_couple(values[2]));
	data->shapes.plane[i]->color = col_to_01(get_couple(values[3]));
	data->shapes.plane[i]->ref = 0;
	if (values[4])
		data->shapes.plane[i]->ref = ft_atoi_double(values[4]);
	data->shapes.plane[i]->id = i;
	i++;
}

void	set_cylinder(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_cilinder	*temp;

	temp = (t_cilinder *)malloc(sizeof(t_cilinder));
	if (!i)
		i = 0;
	data->shapes.cilinder[i] = temp;
	values = ft_split(line, ' ');
	data->shapes.cilinder[i]->origin = get_couple(values[1]);
	data->shapes.cilinder[i]->normal = normalized(get_couple(values[2]));
	data->shapes.cilinder[i]->radious = ft_atoi_double(values[3]);
	data->shapes.cilinder[i]->height = ft_atoi_double(values[4]);
	data->shapes.cilinder[i]->color = col_to_01(get_couple(values[5]));
	data->shapes.cilinder[i]->ref = 0;
	if (values[6])
		data->shapes.cilinder[i]->ref = ft_atoi_double(values[6]);
	data->shapes.cilinder[i]->translate = set_translation(point(0, 0, 0),
			c_mul(data->shapes.cilinder[i]->origin, -1.0));
	data->shapes.cilinder[i]->rotate = set_rotate(get_angle(
				data->shapes.cilinder[i]->normal, vector(0, 0, 1)),
			data->shapes.cilinder[i]->normal, vector(0, 0, 1));
	set_disc(data->shapes.cilinder[i]);
	data->shapes.cilinder[i]->id = i;
	i++;
}

void	set_disc(t_cilinder *cilinder)
{
	cilinder->disc1.normal = c_mul(cilinder->normal, -1);
	cilinder->disc2.normal = copy_couple(cilinder->normal);
	cilinder->disc1.radious = cilinder->radious;
	cilinder->disc2.radious = cilinder->radious;
	cilinder->disc1.origin = cilinder->origin;
	cilinder->disc2.origin = c_sum(c_mul(cilinder->normal,
				cilinder->height), cilinder->origin);
}

void	set_cone(t_data *data, char *line)
{
	char		**values;
	static int	i;
	t_cone		*temp;

	temp = (t_cone *)malloc(sizeof(t_cone));
	if (!i)
		i = 0;
	values = ft_split(line, ' ');
	data->shapes.cone[i] = temp;
	data->shapes.cone[i]->origin = get_couple(values[1]);
	data->shapes.cone[i]->normal = normalized(get_couple(values[2]));
	data->shapes.cone[i]->color = col_to_01(get_couple(values[3]));
	data->shapes.cone[i]->ref = 0;
	if (values[4])
		data->shapes.cone[i]->ref = ft_atoi_double(values[4]);
	data->shapes.cone[i]->translate = set_translation(point(0, 0, 0),
			c_mul(data->shapes.cone[i]->origin, -1.0));
	data->shapes.cone[i]->rotate = set_rotate(get_angle(
				data->shapes.cone[i]->normal, vector(0, 0, 1)),
			data->shapes.cone[i]->normal, vector(0, 0, 1));
	data->shapes.cone[i]->id = i;
	i++;
}
