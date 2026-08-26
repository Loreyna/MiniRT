#include "../../minirt.h"

bool	find_closest_sphere(t_scene *scene, t_ray ray, double *closest_t, int *index)
{
	int		i;
	double	t;

	i = 0;
	*closest_t = INFINITY;
	*index = -1;

	while (i < scene->s_count)
	{
		if (is_sphere_hit(ray, scene->spheres[i], &t))
		{
			if (t > 0 && t < *closest_t)
			{
				*closest_t = t;
				*index = i;
			}
		}
		i++;
	}
	if (*index == -1)
		return (false);
	return (true);
}

bool is_sphere_hit(t_ray ray, t_sphere sphere, double *t)
{
	double	radius;
	t_vec3	oc;
	t_quadratic q;

	radius = sphere.diameter / 2.0;//calculamos el radio

	oc = vec3_sub(ray.origin, sphere.center);// vector desde el centro de la esfera al origen del rayo
	q.a = vec3_dot(ray.direction, ray.direction);
	q.b = 2.0 * vec3_dot(oc, ray.direction); //ecuacion cuadratica (a²+ 2ab + b²)
	q.c = vec3_dot(oc, oc) - radius * radius;

	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;//resultado de lo que hay dentro de la raiz cuadrada

	if (q.discriminant < 0)// no choca
		return (false);
	q.t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);//caluclamos t1
	q.t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);//calculamos t2
	if (q.t1 > 0)
		*t = q.t1;//impacto mas cercano
	else if (q.t2 > 0)
		*t = q.t2;// impacto mas lejano
	else
		return (false);
	return (true);
}
/*
a*t² + b*t + c = 0

a = dirección · dirección
b = 2 * (oc · dirección)
c = oc · oc - radio²
*/
