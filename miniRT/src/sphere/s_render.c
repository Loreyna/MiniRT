/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:34:58 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	calculate_channel(int object_color, t_light_calc light)
{
	int		value;
	double	ambient_aux;
	double	diffuse_aux;

	ambient_aux = light.ambient * (light.ambient_rgb / 255.0);
	diffuse_aux = light.diffuse * (light.light_rgb / 255.0);
	value = object_color * (ambient_aux + diffuse_aux);
	if (value > 255)
		return (255);
	return (value);
}

static uint32_t	calculate_lighting(t_scene *scene, t_hit hit)
{
	double			diffuse;
	double			ambient;
	uint8_t			rgb[3];
	t_light_calc	light;

	diffuse = 0.0;
	ambient = 0.0;
	if (scene->has_light && scene->light)
		diffuse = calculate_diffuse(hit.point, hit.normal, scene->light);
	if (scene->has_ambient && scene->ambient)
		ambient = scene->ambient->light_ratio;
	light.ambient = ambient;
	light.diffuse = diffuse;
	light.ambient_rgb = scene->ambient->rgb[0];
	light.light_rgb = scene->light->rgb[0];
	rgb[0] = calculate_channel(hit.sphere->rgb[0], light);
	light.ambient_rgb = scene->ambient->rgb[1];
	light.light_rgb = scene->light->rgb[1];
	rgb[1] = calculate_channel(hit.sphere->rgb[1], light);
	light.ambient_rgb = scene->ambient->rgb[2];
	light.light_rgb = scene->light->rgb[2];
	rgb[2] = calculate_channel(hit.sphere->rgb[2], light);
	return (rgb_to_hex(rgb));
}

bool	find_closest_sphere(t_scene *scene, t_ray ray,
		double *closest_t, int *index)
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

void	render_sphere(t_scene *scene, mlx_image_t *img)
{
	int			x;
	int			y;
	t_ray		ray;
	t_hit		hit;
	uint32_t	final_color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = create_camera_ray(scene->cam, x, y);
			hit = trace_ray(scene, ray);
			if (hit.hit)
			{
				final_color = calculate_lighting(scene, hit);
				mlx_put_pixel(img, x, y, final_color);
			}
			x++;
		}
		y++;
	}
}
