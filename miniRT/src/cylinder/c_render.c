/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 18:59:23 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:57:30 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	calculate_color_channel(int object_rgb, t_light_calc light)
{
	double	ambient_aux;
	double	diffuse_aux;
	int		color;

	ambient_aux = light.ambient * (light.ambient_rgb / 255.0);
	diffuse_aux = light.diffuse * (light.light_rgb / 255.0);
	color = object_rgb * (ambient_aux + diffuse_aux);
	if (color > 255)
		color = 255;
	return (color);
}

static uint32_t	calculate_lighting(t_scene *scene, t_hit hit)
{
	t_light_calc	light;
	uint8_t			f_rgb[3];
	int				i;

	light.ambient = 0.0;
	light.diffuse = 0.0;
	if (scene->has_light && scene->light)
		light.diffuse = calculate_diffuse(hit.point,
				hit.normal, scene->light);
	if (scene->has_ambient && scene->ambient)
		light.ambient = scene->ambient->light_ratio;
	i = 0;
	while (i < 3)
	{
		light.ambient_rgb = scene->ambient->rgb[i];
		light.light_rgb = scene->light->rgb[i];
		f_rgb[i] = calculate_color_channel(hit.cylinder->rgb[i], light);
		i++;
	}
	return (rgb_to_hex(f_rgb));
}

static bool	find_closest_cylinder(t_scene *scene, t_ray ray,
		double *closest_t, int *index)
{
	int		i;
	double	t;

	i = 0;
	*closest_t = INFINITY;
	*index = -1;
	while (i < scene->cyl_count)
	{
		if (is_cylinder_hit(ray, scene->cylinders[i], &t))
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
	if (!find_closest_cylinder(scene, ray, &t, &index))
		return (hit);
	hit.hit = true;
	hit.t = t;
	hit.point = ray_at(ray, t);
	hit.cylinder = &scene->cylinders[index];
    hit.normal = cylinder_normal(hit.point, *hit.cylinder);
	return (hit);
}

void	render_cylinder (t_scene *scene, mlx_image_t *img)
{
	int		x; 
	int		y;
	t_ray	ray;
	t_hit	hit;
	uint32_t final_color;

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
				final_color = calculate_lighting(scene, hit);
				mlx_put_pixel(img, x, y, final_color);
			}
			x++;
		}
		y++;
	}
}
