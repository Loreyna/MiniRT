/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 17:27:50 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:47:22 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	is_plane_hit(t_ray ray, t_plane plane, double *t)
{
	t_vec3	vector;
	double	numerator;
	double	denominator;

	vector = vec3_sub(plane.point, ray.origin);
	numerator = vec3_dot(vector, plane.normal_v);
	denominator = vec3_dot(ray.direction, plane.normal_v);
	if (fabs(denominator) < 0.000001)
		return (false);
	*t = numerator / denominator;
	if (*t < 0.000001)
		return (false);
	return (true);
}
