/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 17:31:32 by username          #+#    #+#             */
/*   Updated: 2026/09/08 19:43:37 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	t_vec3	normal;

	normal = vec3_sub(point, sphere.center);
	normal = vec3_normalize(normal);
	return (normal);
}

bool	is_sphere_hit(t_ray ray, t_sphere sphere, double *t)
{
	t_quadratic	q;

	q.radius = sphere.diameter / 2.0;
	q.oc = vec3_sub(ray.origin, sphere.center);
	q.a = vec3_dot(ray.direction, ray.direction);
	q.b = 2.0 * vec3_dot(q.oc, ray.direction);
	q.c = vec3_dot(q.oc, q.oc) - q.radius * q.radius;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	if (q.discriminant < 0)
		return (false);
	q.t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	q.t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (q.t1 > 0)
		*t = q.t1;
	else if (q.t2 > 0)
		*t = q.t2;
	else
		return (false);
	return (true);
}
