/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 18:26:22 by username          #+#    #+#             */
/*   Updated: 2026/09/08 18:27:12 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	update_hit_sphere(t_scene *scene, t_ray ray, t_hit *hit)
{
	double	t;
	int		id;

	if (find_closest_sphere(scene, ray, &t, &id))
	{
		if (t < hit->t)
		{
			hit->t = t;
			hit->hit = true;
			hit->sphere = &scene->spheres[id];
			hit->plane = NULL;
			hit->cylinder = NULL;
		}
	}
}

void	update_hit_plane(t_scene *scene, t_ray ray, t_hit *hit)
{
	double	t;
	int		id;

	if (find_closest_plane(scene, ray, &t, &id))
	{
		if (t < hit->t)
		{
			hit->t = t;
			hit->hit = true;
			hit->plane = &scene->planes[id];
			hit->sphere = NULL;
			hit->cylinder = NULL;
		}
	}
}

void	update_hit_cylinder(t_scene *scene, t_ray ray, t_hit *hit)
{
	double	t;
	int		id;

	if (find_closest_cylinder(scene, ray, &t, &id))
	{
		if (t < hit->t)
		{
			hit->t = t;
			hit->hit = true;
			hit->cylinder = &scene->cylinders[id];
			hit->sphere = NULL;
			hit->plane = NULL;
		}
	}
}
