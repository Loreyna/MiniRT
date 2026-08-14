

#include "minirt.h"

/*
typedef struct s_sphere
{
	double	cordinates[3];
	double	diameter;
	uint8_t	rgb[3];
} t_sphere;
*/

t_sphere (t_vec3 center, double radius)
{
    t_sphere sphere;
    sphere.center = center;
    sphere.radius = radius;
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
