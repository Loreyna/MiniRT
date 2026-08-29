/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:53:16 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 18:42:17 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static uint32_t calculate_lighting(t_scene *scene, t_hit hit)
{
	double	diffuse;
	double	ambient;
	int		i;
	int		color;
	uint8_t	f_rgb[3];

	diffuse = 0.0;
	ambient = 0.0;
	if (scene->has_light && scene->light)
		diffuse = calculate_diffuse(hit.point, hit.normal, scene->light);
	if (scene->has_ambient && scene->ambient)
		ambient = scene->ambient->light_ratio;
	i = 0;
	while (i < 3)
	{
		color = hit.plane->rgb[i] *
			(ambient * (scene->ambient->rgb[i] / 255.0)
			+ diffuse * (scene->light->rgb[i] / 255.0));

		if (color > 255)
			color = 255;
		f_rgb[i] = color;
		i++;
	}
	return (rgb_to_hex(f_rgb));
}

bool	find_closest_plane(t_scene *scene, t_ray ray, double *closest_t, int *index)
{
	int		i;
	double	t;

	i = 0;
	*closest_t = INFINITY;
	*index = -1;

	while (i < scene->p_count)
	{
		if (is_plane_hit(ray, scene->planes[i], &t))
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
	if (!find_closest_plane(scene, ray, &t, &index))
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.plane = &scene->planes[index];
	hit.normal = scene->planes[index].normal_v;
	return (hit);
}

void render_plane (t_scene *scene, mlx_image_t *img)
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
