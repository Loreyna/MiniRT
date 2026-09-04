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

double	calculate_diffuse(t_vec3 hit_point, t_vec3 normal, t_light *light)
{
	t_vec3	light_dir;
	double	dot_product;

	if (!light)
		return (0.0);
	light_dir = vec3_normalize(vec3_sub(light->cordinates, hit_point));
	dot_product = vec3_dot(normal, light_dir);
	if (dot_product < 0.0)
		dot_product = 0.0;
	return (dot_product * light->brightness);
}
