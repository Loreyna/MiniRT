/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:41:25 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/03 19:02:23 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static bool	parse_point(t_scene *scene, char **data)
{
	char	**cord;

	cord = ft_split(data[1], ',');
	if (!validate_coords(cord))
	{
		if (cord)
			ft_free_matrix((void ***)&cord);
		return (false);
	}
	scene->planes[scene->p_index].point.x = get_coord_val(cord[0]);
	scene->planes[scene->p_index].point.y = get_coord_val(cord[1]);
	scene->planes[scene->p_index].point.z = get_coord_val(cord[2]);
	ft_free_matrix((void ***)&cord);
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
	scene->planes[scene->p_index].normal_v.x = ft_atof(norm[0]);
	scene->planes[scene->p_index].normal_v.y = ft_atof(norm[1]);
	scene->planes[scene->p_index].normal_v.z = ft_atof(norm[2]);
	ft_free_matrix((void ***)&norm);
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
	scene->planes[scene->p_index].rgb[0] = ft_atoi(rgb[0]);
	scene->planes[scene->p_index].rgb[1] = ft_atoi(rgb[1]);
	scene->planes[scene->p_index].rgb[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void ***)&rgb);
	return (true);
}

bool	parse_plane(t_scene *scene, char **data)
{
	if (!parse_init(4, data))
		return (false);
	if (!parse_point(scene, data))
		return (false);
	if (!parse_orient(scene, data))
		return (false);
	if (!parse_rgb(scene, data))
		return (false);
	scene->p_index++;
	return (true);
}
