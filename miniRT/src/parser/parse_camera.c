/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/18 15:21:27 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minirt.h"

static bool	parse_cords(t_scene *scene, char **data)
{
	char	**cord;

	cord = ft_split(data[1], ',');
	if (!ft_is_str_double(cord[0]) || !ft_is_str_double(cord[1])
		|| !ft_is_str_double(cord[2]))
	{
		ft_free_matrix((void ***)&cord);
		return (false);
	}
	scene->cam->cordinates.x = ft_atof(cord[0]);
	scene->cam->cordinates.y = ft_atof(cord[1]);
	scene->cam->cordinates.z = ft_atof(cord[2]);
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
	scene->cam->orientation.x = ft_atof(norm[0]);
	scene->cam->orientation.y = ft_atof(norm[1]);
	scene->cam->orientation.z = ft_atof(norm[2]);
	ft_free_matrix((void ***)&norm);
	return (true);
}

static bool	parse_fov(t_scene *scene, char **data)
{
	if (!ft_is_str_numeric(data[3]) || ft_atoi(data[3]) > 180
		|| ft_atoi(data[3]) < 0)
		return (false);
	scene->cam->fov = ft_atoi(data[3]);
	return (true);
}

bool	parse_camera(t_scene *scene, char **data)
{
	if (!parse_init(4, data))
		return (false);
	if (!parse_cords(scene, data))
		return (false);
	if (!parse_orient(scene, data))
		return (false);
	if (!parse_fov(scene, data))
		return (false);
	return (true);
}
