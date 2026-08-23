/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/23 16:33:45 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static t_vec3	calculate_direction(t_camera *cam, int x, int y)
{
	t_vec3	pixel;
	t_vec3	direction;

	pixel.x = x - WIDTH / 2;
	pixel.y = HEIGHT / 2 - y;
	pixel.z = 0;

	direction = vec3_sub(pixel, cam->cordinates);
	direction = vec3_normalize(direction);

	return (direction);
}

t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}

static t_ray	create_camera_ray(t_camera *cam, int x, int y)
{
	t_vec3	direction;

	direction = calculate_direction(cam, x, y);
	return (ray_create(cam->cordinates, direction));
}

static bool	find_closest_sphere(t_scene *scene, t_ray ray, double *closest_t, int *index)
{
	/*Busca la esfera más cercana que intersecta con el rayo y devuelve
	su distancia de impacto y su índice dentro de la escena.*/
	int		i;
	double	t;

	i = 0;

	// Inicializamos la distancia mínima con infinito.
	// Cualquier impacto válido estará más cerca que INFINITY.
	*closest_t = INFINITY;
	// -1 significa que todavía no hemos encontrado ninguna esfera.
	*index = -1;

	// Recorremos todas las esferas que existen en la escena.
	while (i < scene->s_count)
	{
	// Comprobamos si el rayo choca con la esfera actual.
	// Si choca, 't' contiene la distancia desde el origen del rayo
	// hasta el punto de impacto.
		if (is_sphere_hit(ray, scene->spheres[i], &t))
		{
	// Nos quedamos solo con impactos que estén delante de la cámara.
	// t <= 0 significaría que el impacto está detrás del origen del rayo.
	// También comprobamos si este impacto está más cerca que el
	// impacto más cercano encontrado hasta ahora.
			if (t > 0 && t < *closest_t)
			{
	// Guardamos la nueva distancia más cercana.
				*closest_t = t;
	// Guardamos qué esfera ha producido ese impacto.
	// Después necesitaremos este índice para calcular: el punto de impacto, la normal
	//el color de la esfera
				*index = i;
			}
		}
		i++;
	}
	// Si el índice sigue siendo -1 significa que hemos recorrido todas
	// las esferas y ninguna ha sido alcanzada por el rayo.
	if (*index == -1)
		return (false);
	// Si hemos llegado aquí, encontramos al menos una esfera.
	return (true);
}

t_vec3	ray_at(t_ray ray, double t)
{
	// Calcula la posición 3D de un punto a una distancia t siguiendo la trayectoria de un rayo.
	t_vec3	displacement;
	t_vec3	position;
	/*
	P(t)=O+D⋅t
	O → origen del rayo (ray.origin)
	D → dirección del rayo (ray.direction)
	t → distancia recorrida
	P(t) → punto del espacio donde está el rayo
	*/

	displacement = vec3_scale(ray.direction, t);
	position = vec3_add(ray.origin, displacement);
	return (position);
}

static t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	t_vec3	normal;
	// Restamos el centro de la esfera al punto de impacto.
	// Esto crea un vector que va desde el centro hasta la superficie.
	normal = vec3_sub(point, sphere.center);
	// Normalizamos el vector para que mida exactamente 1.
	// Esto es necesario para los cálculos de iluminación.
	normal = vec3_normalize(normal);

	return (normal);
}

/*static t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	// Calcula el impacto más cercano de un rayo con los objetos de la escena 
	//y devuelve los datos del choque.
	t_hit	hit;
	double	t;
	int		index;

	// Inicializamos el resultado indicando que todavía no hay impacto.
	hit.hit = false;

	// Buscamos si el rayo alcanza alguna esfera.
	// Si no encuentra ninguna, devolvemos el impacto vacío.
	if (!find_closest_sphere(scene, ray, &t, &index))
		return (hit);

	// Marcamos que el rayo ha golpeado un objeto.
	hit.hit = true;

	// Guardamos la distancia desde el origen del rayo hasta el impacto.
	hit.t = t;

	// Calculamos la posición exacta del punto donde el rayo toca la esfera.
	hit.point = ray_at(ray, t);

	// Calculamos la dirección perpendicular de la superficie en ese punto.
	// Se usará después para calcular la iluminación.
	hit.normal = sphere_normal(
			scene->spheres[index],
			hit.point);
	return (hit);
}*/

/*
//Recorrer la imagen y pedir el color de cada píxel.
void render (t_scene *scene, mlx_image_t *img)
{
	(void)img;
    	int		x; //contadores para ir avanzando en el eje x
	int		y = 0;//y estge en el  eje y
	t_ray	ray;// rayo que sale desde la cámara
	t_hit	hit; // datos del choque

    	while (y < HEIGHT)//bucle doble para ir recorriendo cada pixel.
	{
    		x = 0;
		while (x < WIDTH)
		{
				ray =  create_camera_ray(scene->cam, x , y);//creamos un rayo para el pixel actual
				hit = trace_ray(scene, ray);//calculamos el punto donde choca
				if (hit.hit)
					mlx_put_pixel(img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}
*/

static t_hit	trace_ray(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	double	t;
	int		index;

	hit.hit = false;
	if (!find_closest_sphere(scene, ray, &t, &index))
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.normal = sphere_normal(
			scene->spheres[index],
			hit.point);
	hit.sphere = scene->spheres[index];
	return (hit);
}

void render (t_scene *scene, mlx_image_t *img)
{
    	int		x; 
	int		y;
	t_ray	ray;
	t_hit	hit;

	y = 0;
    	while (y < HEIGHT)
	{
    		x = 0;
		while (x < WIDTH)
		{
				ray =  create_camera_ray(scene->cam, x , y);
				hit = trace_ray(scene, ray);
				if (hit.hit)
					mlx_put_pixel(img, x, y, rgb_to_hex(hit.sphere.rgb));
			x++;
		}
		y++;
	}
}
