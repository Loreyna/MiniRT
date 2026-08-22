#include "../../minirt.h"

/*"Dado un rayo y una esfera, ¿el rayo atraviesa la esfera?
Si la atraviesa, ¿en qué punto ocurre el impacto?"
*/
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

<<<<<<< HEAD
a = dirección · dirección
b = 2 * (oc · dirección)
c = oc · oc - radio²
*/
