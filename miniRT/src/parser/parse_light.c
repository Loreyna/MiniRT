/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:59:43 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/18 16:16:41 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static	bool parse_cords(t_scene *scene, char **data)
{
	char **cord;

	cord = ft_split(data[1], ',');
	if(!ft_is_str_double(cord[0]) || !ft_is_str_double(cord[1]) ||
			!ft_is_str_double(cord[2]))
			{
				ft_free_matrix((void***)&cord);
				return (false);
			}

	scene->light->cordinates.x = ft_atof(cord[0]);
	scene->light->cordinates.y = ft_atof(cord[1]);
	scene->light->cordinates.z = ft_atof(cord[2]);

	ft_free_matrix((void***)&cord);
	return (true);
}
static bool	parse_light_ratio(t_scene *scene, char **data)
{
	if (!ft_is_str_double(data[2]))
		return (false);
	scene->light->brightness = ft_atof(data[2]);
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
	scene->light->rgb[0] = ft_atoi(rgb[0]);
	scene->light->rgb[1] = ft_atoi(rgb[1]);
	scene->light->rgb[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void ***)&rgb);
	return (true);
}

bool parse_light(t_scene *scene, char **data)
{
	if (!parse_init(4, data))
		return (false);
	if (!parse_cords(scene, data))
		return (false);
	if (!parse_light_ratio(scene, data))
		return (false);
	if (!parse_rgb(scene, data))
		return (false);
	return (true);
}
