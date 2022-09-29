/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:03:48 by eperaita          #+#    #+#             */
/*   Updated: 2022/09/27 12:47:06 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	mallocs(t_data *data, int *check)
{
	data->shapes.sphere = (t_sphere **)
		malloc(sizeof(t_sphere *) * data->shapes.max_s);
	if (!data->shapes.sphere)
		error("KO! Malloc error", check, 1);
	data->shapes.cilinder = (t_cilinder **)
		malloc(sizeof(t_cilinder *) * data->shapes.max_cy);
	if (!data->shapes.cilinder)
		error("KO! Malloc error", check, 0);
	data->shapes.plane = (t_plane **)
		malloc(sizeof(t_plane *) * data->shapes.max_p);
	if (!data->shapes.plane)
		error("KO! Malloc error", check, 0);
	data->shapes.cam = (t_cam **)
		malloc(sizeof(t_cam *) * data->shapes.max_c);
	if (!data->shapes.cam)
		error("KO! Malloc error", check, 0);
	data->shapes.light = (t_light **)
		malloc(sizeof(t_light *) * data->shapes.max_l);
	if (!data->shapes.light)
		error("KO! Malloc error", check, 0);
	data->shapes.cone = (t_cone **)
		malloc(sizeof(t_cone *) * data->shapes.max_cn);
	if (!data->shapes.cone)
		error("KO! Malloc error", check, 0);
}

void	alloc_elements(t_data *data, char **lines, int *check)
{
	int	j;
	int	i;

	mallocs(data, check);
	j = -1;
	while (lines[++j] != NULL)
	{
		i = 0;
		while (lines[j][i] == ' ')
			i++;
		if (!ft_strncmp(lines[j] + i, "A", 1))
			set_ambient_light(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "C", 1))
			set_camera(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "L", 1))
			set_light(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "sp", 2))
			set_sphere(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "pl", 2))
			set_plane(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "cy", 2))
			set_cylinder(data, lines[j]);
		else if (!ft_strncmp(lines[j] + i, "cn", 2))
			set_cone(data, lines[j]);
	}
}

int	pass_rt(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}

void	check_input(t_data *data, char **lines, int *check, int j)
{
	int	i;

	while (lines[++j] != NULL)
	{
		i = 0;
		i += pass_rt(lines[j] + i);
		if (!ft_strncmp(lines[j] + i, "A", 1))
			check_ambient_light(lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "C", 1))
			check_camera(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "L", 1))
			check_light(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "sp", 2))
			check_sphere(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "pl", 2))
			check_plane(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "cy", 2))
			check_cylinder(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "cn", 2))
			check_cone(data, lines[j], check);
		else if (!ft_strncmp(lines[j] + i, "SKB", 3))
			data->shapes.skybox->active = 1;
		else if (ft_strncmp(lines[j] + i, "//", 2) && lines[j] != NULL)
			input_error("KO! Input error", lines[j], check, 0);
	}
}

void	get_input(t_data *data, char *argv, int check)
{
	int		fd;
	char	*file;
	char	**lines;

	check_rt(argv, &check);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		input_error("KO! Unable to open file", argv, &check, 1);
	file = get_file(fd, &check);
	lines = ft_split(file, '\n');
	free (file);
	if (lines == NULL)
		error("KO! Empty file", &check, 1);
	data->shapes.skybox = malloc(sizeof(t_skybox));
	data->shapes.skybox->active = 0;
	check_input(data, lines, &check, -1);
	if (check || data->shapes.max_c == 0)
	{
		free2d(lines);
		exit(1);
	}
	alloc_elements(data, lines, &check);
	free2d(lines);
	set_img(data, &check);
	if (check)
		free_exit(data);
}
