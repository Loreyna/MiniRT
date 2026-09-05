/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 18:59:23 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:57:30 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	find_closest_cylinder(t_scene *scene, t_ray ray,
		double *closest_t, int *index)
{
	int		i;
	double	t;

	i = 0;
	*closest_t = INFINITY;
	*index = -1;
	while (i < scene->cyl_count)
	{
		if (is_cylinder_hit(ray, scene->cylinders[i], &t))
		{
			if (t > 0 && t < *closest_t)
			{
				*closest_t = t;
				*index = i;
			}
		}
		i++;
	}
	if (*index == -1)
		return (false);
	return (true);
}
