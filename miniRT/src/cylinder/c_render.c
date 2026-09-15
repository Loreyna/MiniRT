/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 18:59:23 by username          #+#    #+#             */
/*   Updated: 2026/09/08 19:43:08 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec3	cylinder_normal(t_vec3 hit_point, t_cylinder cylinder)
{
	t_vec3	normal;
	t_vec3	to_hit;
	double	projection;

	cylinder.axis_v = vec3_normalize(cylinder.axis_v);
	to_hit = vec3_sub(hit_point, cylinder.center);
	projection = vec3_dot(to_hit, cylinder.axis_v);
	if (projection >= (cylinder.height / 2.0) - 0.001)
		return (cylinder.axis_v);
	if (projection <= -(cylinder.height / 2.0) + 0.001)
		return (vec3_scale(cylinder.axis_v, -1.0));
	normal = vec3_sub(to_hit, vec3_scale(cylinder.axis_v, projection));
	return (vec3_normalize(normal));
}

bool	find_closest_cylinder(t_scene *scene, t_ray ray, double *closest_t,
		int *index)
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
