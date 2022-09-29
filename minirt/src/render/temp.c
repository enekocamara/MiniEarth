/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:07:42 by ecamara           #+#    #+#             */
/*   Updated: 2022/09/29 15:59:37 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

typedef struct s_uv_map
{
	int		height;
	int		width;
	t_couple	color_a;
	t_couple	color_b;
}t_uv_map;

t_uv_map	uv_checkers(int width, int height, t_couple color_a, t_couple color_b)
{
	t_uv_map	uv_map;

	uv_map.height = height;
	uv_map.width = width;
	uv_map.color_a = color_a;
	uv_map.color_b = color_b;
	return (uv_map);
}

int uv_pattern_at(t_uv_map pattern, double u, double v)
{
	int	i;
	int	j;

	i = ((int)(v * pattern.height)) % 2;
	j = ((int)(u * pattern.width)) % 2;
	return ((i + j) % 2);
}

t_uv	spherical_map(t_couple point)
{
  // compute the azimuthal angle
  // -π < theta <= π
  // angle increases clockwise as viewed from above,
  // which is opposite of what we want, but we'll fix it later.

  
	double theta = atan2(point.x, point.z);

  // vec is the vector pointing from the sphere's origin (the world origin)
  // to the point, which will also happen to be exactly equal to the sphere's
  // radius.
  t_couple vec = vector(point.x, point.y, point.z);
  double radius = len(vec);

  // compute the polar angle
  // 0 <= phi <= π
  double phi = acos(point.y / radius);

  // -0.5 < raw_u <= 0.5
  double raw_u = theta / (2 * M_PI);

  // 0 <= u < 1
  // here's also where we fix the direction of u. Subtract it from 1,
 //  so that it increases counterclockwise as viewed from above.
	double u = 1 - (raw_u + 0.5);

//  # we want v to be 0 at the south pole of the sphere,
  //# and 1 at the north pole, so we have to "flip it over"
  //# by subtracting it from 1.
	double v = 1 - phi / M_PI;
	return (uv(u, v));
}

t_couple	get_color_sphere(t_shapes *elem, t_couple point, t_img texture)
{
	t_uv_map	uv_map;
	int			temp;


	//printf("[%lf][%lf][%lf]\n", point.x, point.y, point.z);
	uv_map = uv_checkers(10, 10, vector(0,0,0), vector(1,1,1));
	t_uv map = spherical_map(point);
	temp = (map.x * 8192) + elem->earth->index;
	if (temp >= 8192)
		temp -= 8192;
	return (col_to_01(int_to_col01(texture.add[(int)clamp(0, 4096 * 8192, (int)(map.y * 4096) * 8192 + temp)])));
	/*elem->skybox->textures.add[]
	int temp = uv_pattern_at(uv_map, map.x, map.y);
	return (vector(temp, temp, temp));*/
}
