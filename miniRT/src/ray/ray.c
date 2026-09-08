/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 16:56:46 by username          #+#    #+#             */
/*   Updated: 2026/09/08 18:44:51 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec3	ray_at(t_ray ray, double t)
{
	t_vec3	displacement;
	t_vec3	position;

	displacement = vec3_scale(ray.direction, t);
	position = vec3_add(ray.origin, displacement);
	return (position);
}

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}

static void	calculate_hit_properties(t_ray ray, t_hit *hit)
{
	hit->point = ray_at(ray, hit->t);
	if (hit->sphere)
		hit->normal = sphere_normal(*hit->sphere, hit->point);
	else if (hit->plane)
		hit->normal = hit->plane->normal_v;
	else if (hit->cylinder)
		hit->normal = cylinder_normal(hit->point, *hit->cylinder);
}

t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;

	hit.hit = false;
	hit.t = INFINITY;
	hit.sphere = NULL;
	hit.plane = NULL;
	hit.cylinder = NULL;
	update_hit_sphere(scene, ray, &hit);
	update_hit_plane(scene, ray, &hit);
	update_hit_cylinder(scene, ray, &hit);
	if (hit.hit)
		calculate_hit_properties(ray, &hit);
	return (hit);
}
