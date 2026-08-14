

#include "minirt.h"

/*
typedef struct s_sphere
{
	t_cord	center;
	double	diameter;
	uint8_t	rgb[3];
} t_sphere;
*/

t_sphere sphere_create (t_cord center, double diameter, uint8_t rgb[3])
{
	t_sphere sphere;

	sphere.center = center;
	sphere.diameter = diameter;
	sphere.rgb[0] = rgb[0];
	sphere.rgb[1] = rgb[1];
	sphere.rgb[2] = rgb[2];
	return (sphere);
}

sphere_hit()
{
    
}

/*La normal es un vector que indica hacia dónde está orientada
la superficie en el punto donde el rayo ha impactado. Después se
compara con la dirección de la luz para calcular cuánta
iluminación recibe ese punto.*/
sphere_normal()
{
    
}
