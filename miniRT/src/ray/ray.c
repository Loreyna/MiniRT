/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 16:56:46 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:37:24 by lrey-mol         ###   ########.fr       */
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
