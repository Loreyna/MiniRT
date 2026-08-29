/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:17:35 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 17:33:01 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static bool	parse_center(t_scene *scene, char **data)
{
	char	**cord;

	cord = ft_split(data[1], ',');
	if (!ft_is_str_double(cord[0]) || !ft_is_str_double(cord[1])
		|| !ft_is_str_double(cord[2]))
	{
		ft_free_matrix((void ***)&cord);
		return (false);
	}
	scene->cylinders[scene->cyl_index].center.x = ft_atof(cord[0]);
	scene->cylinders[scene->cyl_index].center.y = ft_atof(cord[1]);
	scene->cylinders[scene->cyl_index].center.z = ft_atof(cord[2]);
	ft_free_matrix((void ***) &cord);
	return (true);
}

static bool	parse_orient(t_scene *scene, char **data)
{
	char	**norm;

	norm = ft_split(data[2], ',');
	if (!ft_is_str_double(norm[0]) || !ft_is_str_double(norm[1])
		|| !ft_is_str_double(norm[2]))
	{
		ft_free_matrix((void ***)&norm);
		return (false);
	}
	if (((ft_atof(norm[0]) < -1) && (ft_atof(norm[0]) > 1))
		|| ((ft_atof(norm[1]) < -1) && (ft_atof(norm[1]) > 1))
		|| ((ft_atof(norm[2]) < -1) && (ft_atof(norm[2]) > 1)))
	{
		ft_free_matrix((void ***)&norm);
		return (false);
	}
	scene->cylinders[scene->cyl_index].axis_v.x = ft_atof(norm[0]);
	scene->cylinders[scene->cyl_index].axis_v.y = ft_atof(norm[1]);
	scene->cylinders[scene->cyl_index].axis_v.z = ft_atof(norm[2]);
	ft_free_matrix((void ***)&norm);
	return (true);
}

static bool	parse_dimentions(t_scene *scene, char **data)
{
	double	diameter;
    double  height;

	if (!ft_is_str_double(data[3]))
		return (false);
	diameter = atof(data[3]);
	if (diameter <= 0)
		return (false);
	scene->cylinders[scene->cyl_index].diameter = diameter;
    if (!ft_is_str_double(data[4]))
		return (false);
	height = atof(data[4]);
	if (height <= 0)
		return (false);
	scene->cylinders[scene->cyl_index].height =height;
	return (true);
}

static bool	parse_rgb(t_scene *scene, char **data)
{
	char	**rgb;

	rgb = ft_split(data[5], ',');
	if (!ft_is_str_numeric(rgb[0]) || !ft_is_str_numeric(rgb[1])
		|| !ft_is_str_numeric(rgb[2]) || !rgb_check(rgb))
	{
		ft_free_matrix((void ***)&rgb);
		return (false);
	}
	scene->cylinders[scene->cyl_index].rgb[0] = ft_atoi(rgb[0]);
	scene->cylinders[scene->cyl_index].rgb[1] = ft_atoi(rgb[1]);
	scene->cylinders[scene->cyl_index].rgb[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void ***)&rgb);
	return (true);
}

bool parse_cylinder(t_scene *scene, char **data)
{
    if (!parse_init(6, data))
		return (false);
	if (!parse_center(scene, data))
		return (false);
    if (!parse_orient(scene, data))
		return (false);
    if (!parse_dimentions(scene, data))
		return (false);
    if (!parse_rgb(scene, data))
		return (false);
    scene->cyl_index++;
    return (true);
}