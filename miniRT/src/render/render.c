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

static uint8_t get_hit_color(t_hit hit, int channel)
{
    if (hit.sphere)
        return (hit.sphere->rgb[channel]);
    if (hit.plane)
        return (hit.plane->rgb[channel]);
    if (hit.cylinder)
        return (hit.cylinder->rgb[channel]);
    return (0);
}

static uint32_t calculate_lighting(t_scene *scene, t_hit hit)
{
    t_light_calc    light;
    uint8_t         f_rgb[3];
    uint8_t         base_color;
    int             i;

    light.ambient = 0.0;
    light.diffuse = 0.0;
    if (scene->has_light && scene->light)
        light.diffuse = calculate_diffuse(hit.point, hit.normal, scene->light);
    if (scene->has_ambient && scene->ambient)
        light.ambient = scene->ambient->light_ratio;
    i = 0;
    while (i < 3)
    {
        light.ambient_rgb = scene->ambient->rgb[i];
        light.light_rgb = scene->light->rgb[i];
        base_color = get_hit_color(hit, i);
        f_rgb[i] = calculate_color_channel(base_color, light);
        i++;
    }
    return (rgb_to_hex(f_rgb));
}

static void update_hit_sphere(t_scene *scene, t_ray ray, t_hit *hit)
{
    double  t;
    int     id;

    if (find_closest_sphere(scene, ray, &t, &id))
    {
        if (t < hit->t)
        {
            hit->t = t;
            hit->hit = true;
            hit->sphere = &scene->spheres[id];
            hit->plane = NULL;
            hit->cylinder = NULL;
        }
    }
}

static void update_hit_plane(t_scene *scene, t_ray ray, t_hit *hit)
{
    double  t;
    int     id;

    if (find_closest_plane(scene, ray, &t, &id))
    {
        if (t < hit->t)
        {
            hit->t = t;
            hit->hit = true;
            hit->plane = &scene->planes[id];
            hit->sphere = NULL;
            hit->cylinder = NULL;
        }
    }
}

static void update_hit_cylinder(t_scene *scene, t_ray ray, t_hit *hit)
{
    double  t;
    int     id;

    if (find_closest_cylinder(scene, ray, &t, &id))
    {
        if (t < hit->t)
        {
            hit->t = t;
            hit->hit = true;
            hit->cylinder = &scene->cylinders[id];
            hit->sphere = NULL;
            hit->plane = NULL;
        }
    }
}

static void calculate_hit_properties(t_ray ray, t_hit *hit)
{
    hit->point = ray_at(ray, hit->t);
    if (hit->sphere)
        hit->normal = sphere_normal(*hit->sphere, hit->point);
    else if (hit->plane)
        hit->normal = hit->plane->normal_v;
    else if (hit->cylinder)
        hit->normal = cylinder_normal(hit->point, *hit->cylinder);
}

t_hit trace_ray(t_scene *scene, t_ray ray)
{
    t_hit hit;

    hit.hit = false;
    hit.t = INFINITY;
    hit.sphere = NULL;
    hit.plane = NULL;
    hit.cylinder = NULL;
    
    update_hit_sphere(scene, ray, &hit);
    update_hit_plane(scene, ray, &hit);
    update_hit_cylinder(scene, ray, &hit);
    
    if (hit.hit)
        calculate_hit_properties(ray, &hit);
        
    return (hit);
}

void render_scene(t_scene *scene, mlx_image_t *img)
{
    int         x;
    int         y;
    t_ray       ray;
    t_hit       hit;

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
