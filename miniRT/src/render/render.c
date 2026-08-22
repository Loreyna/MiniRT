/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/20 18:44:34 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

/*
pixel_x = x - WIDTH / 2
pixel_y = HEIGHT / 2 - y
*/


t_vec3	get_ray_direction(t_camera *cam, int x, int y);
/*
convierte
pixel (x,y)
     ↓
dirección 3D del rayo
*/

mlx_image_t render(t_scene *scene,  mlx_image_t img)
{
	int x;
	int y;

	y = 0;

	while (y < HEIGHT)
	{	
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_create(scene->cam->cordinates, );//direccioˊn=punto_pixel−posicion_camara

			x++;
		}
		y++;
	}
	
}