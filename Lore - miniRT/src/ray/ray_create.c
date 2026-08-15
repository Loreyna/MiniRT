#include "../../minirt.h"

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}
