/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:19:12 by username          #+#    #+#             */
/*   Updated: 2026/09/08 20:15:03 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	check_cap(t_ray ray, t_cylinder cyl, int top, double *best_t)
{
	double	denom;
	double	t;
	t_vec3	center;
	t_vec3	normal;
	t_vec3	to_hit;

	normal = cyl.axis_v;
	if (!top)
		normal = vec3_scale(cyl.axis_v, -1.0);
	center = vec3_add(cyl.center, vec3_scale(normal, cyl.height / 2.0));
	denom = vec3_dot(ray.direction, normal);
	if (fabs(denom) < 0.000001)
		return ;
	t = vec3_dot(vec3_sub(center, ray.origin), normal) / denom;
	if (t <= 0.001 || t >= *best_t)
		return ;
	to_hit = vec3_sub(ray_at(ray, t), center);
	if (vec3_dot(to_hit, to_hit) <= (cyl.diameter / 2.0) * (cyl.diameter / 2.0))
		*best_t = t;
}

static bool	validate_hit_height(t_ray ray, t_cylinder cylinder, double t)
{
	t_vec3	hit_point;
	t_vec3	hit_to_center;
	double	height;

	hit_point = ray_at(ray, t);
	hit_to_center = vec3_sub(hit_point, cylinder.center);
	height = vec3_dot(hit_to_center, cylinder.axis_v);
	if (height >= -cylinder.height / 2.0 && height <= cylinder.height / 2.0)
		return (true);
	return (false);
}

static bool	calculate_cylinder_quadratic(t_ray ray, t_cylinder cylinder,
		t_quadratic *q)
{
	double	dot_dir_axis;
	double	dot_oc_axis;

	q->oc = vec3_sub(ray.origin, cylinder.center);
	dot_dir_axis = vec3_dot(ray.direction, cylinder.axis_v);
	q->a = vec3_dot(ray.direction, ray.direction) - (dot_dir_axis
			* dot_dir_axis);
	if (fabs(q->a) < 0.000001)
		return (false);
	dot_oc_axis = vec3_dot(q->oc, cylinder.axis_v);
	q->b = 2.0 * (vec3_dot(q->oc, ray.direction) - (dot_oc_axis
				* dot_dir_axis));
	q->radius = cylinder.diameter / 2.0;
	q->c = vec3_dot(q->oc, q->oc) - (dot_oc_axis * dot_oc_axis) - (q->radius
			* q->radius);
	q->discriminant = q->b * q->b - 4.0 * q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	return (true);
}

static double	check_body(t_ray ray, t_cylinder cylinder)
{
	t_quadratic	q;
	double		t1;
	double		t2;
	double		temp;

	if (!calculate_cylinder_quadratic(ray, cylinder, &q))
		return (INFINITY);
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (t1 > 0.001 && validate_hit_height(ray, cylinder, t1))
		return (t1);
	if (t2 > 0.001 && validate_hit_height(ray, cylinder, t2))
		return (t2);
	return (INFINITY);
}

bool	is_cylinder_hit(t_ray ray, t_cylinder cylinder, double *t)
{
	double	best_t;

	cylinder.axis_v = vec3_normalize(cylinder.axis_v);
	best_t = check_body(ray, cylinder);
	check_cap(ray, cylinder, 1, &best_t);
	check_cap(ray, cylinder, 0, &best_t);
	if (best_t != INFINITY)
	{
		*t = best_t;
		return (true);
	}
	return (false);
}
