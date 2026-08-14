
#include "minirt.h"

//obtener un punto cualquiera del rayo.

t_vec3 ray_at (t_ray ray, double t)
{
	t_vec3 displacement;
	t_vec3 position;
	
	displacement = vec3_scale(ray.direction, t);
	position = vec3_add(ray.origin, displacement);
	return (position);
}

/*
t_vec3 ray_at (t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}
*/
