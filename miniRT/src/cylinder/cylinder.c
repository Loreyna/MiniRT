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

static bool	validate_hit_height(t_ray ray,
	t_cylinder cylinder, double t, double *out_t)
{
	t_vec3	hit_point;
	t_vec3	hit_to_center;
	double	height;

	hit_point = ray_at(ray, t);
	hit_to_center = vec3_sub(hit_point, cylinder.center);
	height = vec3_dot(hit_to_center, cylinder.axis_v);
	if (height >= -cylinder.height / 2 && height <= cylinder.height / 2)
	{
		*out_t = t;
		return (true);
	}
	return (false);
}

static bool	calculate_cylinder_quadratic(t_ray ray,
	t_cylinder	cylinder, t_quadratic *q)
{
	double	dot_dir_axis;
	double	dot_oc_axis;

	cylinder.axis_v = vec3_normalize(cylinder.axis_v);
	q->oc = vec3_sub(ray.origin, cylinder.center);
	dot_dir_axis = vec3_dot(ray.direction, cylinder.axis_v);
	q->a = vec3_dot(ray.direction, ray.direction)
		- (dot_dir_axis * dot_dir_axis);
	if (fabs(q->a) < 0.000001)
		return (false);
	dot_oc_axis = vec3_dot(q->oc, cylinder.axis_v);
	q->b = 2.0 * (vec3_dot(q->oc, ray.direction)
			-(dot_oc_axis * dot_dir_axis));
	q->radius = cylinder.diameter / 2;
	q->c = vec3_dot(q->oc, q->oc) - (dot_oc_axis * dot_oc_axis)
		- (q->radius * q->radius);
	q->discriminant = q->b * q->b - 4.0 * q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	return (true);
}

bool	is_cylinder_hit(t_ray ray, t_cylinder cylinder, double *t)
{
	t_quadratic	q;
	double		sqrt_d;
	double		t1;
	double		t2;
	double		temp;

	if (!calculate_cylinder_quadratic(ray, cylinder, &q))
		return (false);
	sqrt_d = sqrt(q.discriminant);
	t1 = (-q.b - sqrt_d) / (2.0 * q.a);
	t2 = (-q.b + sqrt_d) / (2.0 * q.a);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (t1 > 0 && validate_hit_height(ray, cylinder, t1, t))
		return (true);
	if (t2 > 0 && validate_hit_height(ray, cylinder, t2, t))
		return (true);
	return (false);
}
/*
bool is_cylinder_hit(t_ray ray, t_cylinder cylinder, double * t)
{
t_quadratic	q;
double		dot_dir_axis;
double		dot_oc_axis;

cylinder.axis_v = vec3_normalize(cylinder.axis_v);
q.oc = vec3_sub(ray.origin, cylinder.center);
dot_dir_axis = vec3_dot(ray.direction, cylinder.axis_v);
q.a = vec3_dot(ray.direction, ray.direction) - (dot_dir_axis * dot_dir_axis);
if (fabs(q.a) < 0.000001)
return (false);
dot_oc_axis = vec3_dot(q.oc, cylinder.axis_v);
q.b = 2.0 * ((vec3_dot(q.oc, ray.direction)) - (dot_oc_axis * dot_dir_axis));
q.radius = cylinder.diameter / 2;
q.c = vec3_dot(q.oc, q.oc) - (dot_oc_axis * dot_oc_axis) - (q.radius * q.radius);
q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
if (q.discriminant < 0)
return (false);
double	sqrt_d = sqrt(q.discriminant);
double	t1 = (-q.b - sqrt_d) / (2.0 *q.a);
double	t2 = (-q.b + sqrt_d) / (2.0 *q.a);
if (t1 > t2)
{
double	temp = t1;
t1 = t2;
t2 = temp;
}
if (t1 > 0 && validate_hit_height(ray, cylinder, t1, t))
return (true);
if (t2 > 0 && validate_hit_height(ray, cylinder, t2, t))
return (true);
return (false);
}
*/
