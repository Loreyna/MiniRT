/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:09:57 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:54:00 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
static	bool in_shadow(t_vec3 hit_point, t_vec3 light_dir, t_vec3 normal, t_scene *scene)
{
	t_ray	ray;
	t_vec3	shadow_origin;
	//t_vec3	distance;
	t_hit	hit;
	
	//distance = vec3_sub(scene->light->cordinates, hit_point);
	//distance = vec3_lenth(distance);
	shadow_origin = vec3_add(hit_point, vec3_scale(normal, 0.0001));
	ray = ray_create(shadow_origin, light_dir);
	hit = trace_ray(scene, ray);
	if(hit.hit)
		return (true);
	else
		return (false);
}

double	calculate_diffuse(t_vec3 hit_point, t_vec3 normal, t_scene *scene)
{
	t_vec3	light_dir;
	double	dot_product;
	t_light *light;
	
	light = scene->light;
	if (!light)
		return (0.0);
	light_dir = vec3_normalize(vec3_sub(light->cordinates, hit_point));
	dot_product = vec3_dot(normal, light_dir);
	if (dot_product < 0.0)
		dot_product = 0.0;
	if (in_shadow(hit_point, light_dir, normal, scene))
		return (0.0);
	return (dot_product * light->brightness);
}	
