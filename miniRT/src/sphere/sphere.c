#include "../../minirt.h"

/*typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	uint8_t	rgb[3];
} t_sphere;*/

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
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;
*/
void	sphere_hit(t_ray ray, t_sphere sphere) //((origen + direccion ∗ t) − centro)² = R²
{
	double radius;
	t_vec3 oc; // oc = origen − centro --> (oc + direccion * t)² = R²
	double a;
	double b;
	double c;
	double discriminant;
	//(a+b)² = a²+2ab+b²
	radius = sphere.diameter / 2.0;
//	oc = vec3_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4.0 * a * c;
	if(discriminant < 0)
	{
		//no hay choque
	}
	else
	{
		//si lo hay
		//calcular t
	}

}

/*La normal es un vector que indica hacia dónde está orientada
la superficie en el punto donde el rayo ha impactado. Después se
compara con la dirección de la luz para calcular cuánta
iluminación recibe ese punto.*/
//sphere_normal()
//{
//}
