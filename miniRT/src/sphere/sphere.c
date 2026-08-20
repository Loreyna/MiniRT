#include "../../minirt.h"

t_sphere sphere_create (t_vec3 center, double diameter, uint8_t rgb[3])
{
	t_sphere sphere;

	sphere.center = center;
	sphere.diameter = diameter;
	sphere.rgb[0] = rgb[0];
	sphere.rgb[1] = rgb[1];
	sphere.rgb[2] = rgb[2];
	return (sphere);
}
/*"Dado un rayo y una esfera, ¿el rayo atraviesa la esfera?
Si la atraviesa, ¿en qué punto ocurre el impacto?"
*/
bool is_sphere_hit(t_ray ray, t_sphere sphere, double *t)
{
	double	radius;
	t_vec3	oc;
	t_quadratic q;

	radius = sphere.diameter / 2.0;//calculamos el radio

	oc = vec3_sub(ray.origin, sphere.center);
	q.a = vec3_dot(ray.direction, ray.direction);
	q.b = 2.0 * vec3_dot(oc, ray.direction); //ecuacion cuadratica (a²+ 2ab + b²)
	q.c = vec3_dot(oc, oc) - radius * radius;

	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;//resultado de la raiz cuadrada

	if (q.discriminant < 0)// no choca
		return (false);
	q.t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);//caluclamos t1
	q.t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);//calculamos t2
	if (q.t1 > 0)
		*t = q.t1;//primer impacto
	else if (q.t2 > 0)
		*t = q.t2;// segundo impacto
	else
		return (false);
	return (true);
}
/*
a*t² + b*t + c = 0

<<<<<<< HEAD
a = dirección · dirección
b = 2 * (oc · dirección)
c = oc · oc - radio²
*/
