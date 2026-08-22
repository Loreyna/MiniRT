/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:37:21 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/20 17:57:46 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

// calcular el punto 3D donde ocurrió el impacto.
t_vec3	ray_at(t_ray ray, double t)
{
	t_vec3	displacement;
	t_vec3	position;

	displacement = vec3_scale(ray.direction, t);
	position = vec3_add(ray.origin, displacement);
	return (position);
}
