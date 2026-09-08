/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by username          #+#    #+#             */
/*   Updated: 2026/09/08 18:45:43 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	calculate_color_channel(int object_rgb, t_light_calc light)
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

static uint8_t	get_hit_color(t_hit hit, int channel)
{
	if (hit.sphere)
		return (hit.sphere->rgb[channel]);
	if (hit.plane)
		return (hit.plane->rgb[channel]);
	if (hit.cylinder)
		return (hit.cylinder->rgb[channel]);
	return (0);
}

static uint32_t	calculate_lighting(t_scene *scene, t_hit hit)
{
	t_light_calc	light;
	uint8_t			f_rgb[3];
	uint8_t			base_color;
	int				i;

	light.ambient = 0.0;
	light.diffuse = 0.0;
	if (scene->has_light && scene->light)
		light.diffuse = calculate_diffuse(hit.point, hit.normal, scene);
	if (scene->has_ambient && scene->ambient)
		light.ambient = scene->ambient->light_ratio;
	i = 0;
	while (i < 3)
	{
		if (scene->has_ambient)
			light.ambient_rgb = scene->ambient->rgb[i];
		if (scene->has_light)
			light.light_rgb = scene->light->rgb[i];
		base_color = get_hit_color(hit, i);
		f_rgb[i] = calculate_color_channel(base_color, light);
		i++;
	}
	return (rgb_to_hex(f_rgb));
}

void	render_scene(t_scene *scene, mlx_image_t *img)
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
			ray = create_camera_ray(scene->cam, x, y);
			hit = trace_ray(scene, ray);
			if (hit.hit)
				mlx_put_pixel(img, x, y, calculate_lighting(scene, hit));
			x++;
		}
		y++;
	}
}
