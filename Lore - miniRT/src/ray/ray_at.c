#include "../../minirt.h"

//obtener un punto cualquiera del rayo.P(t) = origin + direction * t

t_vec3	ray_at (t_ray ray, double t)
{
	t_vec3	displacement;
	t_vec3	position;

	displacement = vec3_scale(ray.direction, t);
	position = vec3_add(ray.origin, displacement);
	return (position);
}
