/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/03 17:28:24 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static uint32_t calculate_lighting(t_scene *scene, t_hit hit)//reducir o dividir
{
	double  diffuse;
	double  ambient;
	int     r;
	int     g;
	int     b;
	uint8_t f_rgb[3];

	diffuse = 0.0;
	ambient = 0.0;
	// Only calculate light values if they were provided in the .rt file
	if (scene->has_light && scene->light)
		diffuse = calculate_diffuse(hit.point, hit.normal, scene->light);
	if (scene->has_ambient && scene->ambient)
		ambient = scene->ambient->light_ratio;

	 
	double ambient_aux = 0.0; 
	double diffuse_aux = 0.0;

	if (scene->has_ambient && scene->ambient)
		ambient_aux = ambient * (scene->ambient->rgb[0] / 255.0);
	if (scene->has_light && scene->light)
		diffuse_aux = diffuse * (scene->light->rgb[0] / 255.0);
	r = hit.sphere->rgb[0] * (diffuse_aux + ambient_aux);

	if (scene->has_ambient && scene->ambient)
		ambient_aux = ambient * (scene->ambient->rgb[1] / 255.0);
	if (scene->has_light && scene->light)
		diffuse_aux = diffuse * (scene->light->rgb[1] / 255.0);
	g = hit.sphere->rgb[1] * (diffuse_aux + ambient_aux);

	if (scene->has_ambient && scene->ambient)
		ambient_aux = ambient * (scene->ambient->rgb[2] / 255.0);
	if (scene->has_light && scene->light)
		diffuse_aux = diffuse * (scene->light->rgb[2] / 255.0);
	b = hit.sphere->rgb[2] * (diffuse_aux + ambient_aux);

	if(r > 255)
		f_rgb[0] = 255;
	else 
		f_rgb[0] = r;
	if(g > 255)
		f_rgb[1] = 255;
	else 
		f_rgb[1] = g;
	if(b > 255)
		f_rgb[2] = 255;
	else 
		f_rgb[2] = b;

	return (rgb_to_hex(f_rgb));
}

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
	hit.sphere = &scene->spheres[index];
	return (hit);
}

void render_sphere (t_scene *scene, mlx_image_t *img)
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
				{
					uint32_t final_color = calculate_lighting(scene, hit);
					mlx_put_pixel(img, x, y, final_color);
				}
			x++;
		}
		y++;
	}
}
