/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:53:20 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/19 15:51:24 by lrey-mol         ###   ########.fr       */
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
	scene->spheres[scene->s_index].center.x = ft_atof(cord[0]);
	scene->spheres[scene->s_index].center.y = ft_atof(cord[1]);
	scene->spheres[scene->s_index].center.z = ft_atof(cord[2]);
	ft_free_matrix((void ***) &cord);
	return (true);
}

static bool	parse_diameter(t_scene *scene, char **data)
{
	double	diameter;

	if (!ft_is_str_double(data[2]))
		return (false);
	diameter = atof(data[2]);
	if (diameter <= 0)
		return (false);
	scene->spheres[scene->s_index].diameter = atof(data[2]);
	return (true);
}

static bool	parse_rgb(t_scene *scene, char **data)
{
	char	**rgb;

	rgb = ft_split(data[3], ',');
	if (!ft_is_str_numeric(rgb[0]) || !ft_is_str_numeric(rgb[1])
		|| !ft_is_str_numeric(rgb[2]) || !rgb_check(rgb))
	{
		ft_free_matrix((void ***)&rgb);
		return (false);
	}
	scene->spheres[scene->s_index].rgb[0] = ft_atoi(rgb[0]);
	scene->spheres[scene->s_index].rgb[1] = ft_atoi(rgb[1]);
	scene->spheres[scene->s_index].rgb[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void ***)&rgb);
	return (true);
}

bool	parse_sphere(t_scene *scene, char **data)
{
	if (!parse_init(4, data))
		return (false);
	if (!parse_center(scene, data))
		return (false);
	if (!parse_diameter(scene, data))
		return (false);
	if (!parse_rgb(scene, data))
		return (false);
	scene->s_index++;
	return (true);
}
