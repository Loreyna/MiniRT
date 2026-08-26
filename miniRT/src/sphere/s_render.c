/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 18:39:01 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/26 18:19:40 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static double calculate_diffuse(t_vec3 hit_point, t_vec3 normal, t_light *light)
{
	t_vec3 light_dir;
	double dot_product;

	if (!light)
		return (0.0);
	// Get direction from the hit point to the light's coordinates
	light_dir = vec3_normalize(vec3_sub(light->cordinates, hit_point));
	dot_product = vec3_dot(normal, light_dir);
	// Clamp negative values to 0 (the dark side of the sphere)
	if (dot_product < 0.0)
		dot_product = 0.0;  
	return (dot_product * light->brightness);
}

static uint32_t calculate_lighting(t_scene *scene, t_hit hit)
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
	// Mix Object Color with (Ambient + Diffuse) 
	r = hit.sphere->rgb[0] * (ambient * (scene->ambient->rgb[0] / 255.0) 
		+ diffuse * (scene->light->rgb[0] / 255.0));
	g = hit.sphere->rgb[1] * (ambient * (scene->ambient->rgb[1] / 255.0) 
		+ diffuse * (scene->light->rgb[1] / 255.0));
	b = hit.sphere->rgb[2] * (ambient * (scene->ambient->rgb[2] / 255.0) 
		+ diffuse * (scene->light->rgb[2] / 255.0));
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

static void get_camera_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up)
{
	t_vec3 global_up;

	// We use the world's Y-axis as a guide to figure out which way is "Right"
	global_up.x = 0;
	global_up.y = 1;
	global_up.z = 0;

	// Safety check: If the camera is looking straight up or straight down,
	// the cross product fails. We change the guide vector to the Z-axis.
	if (fabs(forward.x) < 0.00001 && fabs(forward.z) < 0.00001)
	{
		global_up.y = 0;
		global_up.z = 1;
	}

	// Right is perpendicular to Forward and Global Up
	*right = vec3_normalize(vec3_cross(global_up, forward));
	// Local Up is perpendicular to Forward and Right
	*up = vec3_cross(forward, *right);
}

static t_vec3 calculate_direction(t_camera *cam, int x, int y)
{
	double  aspect_ratio;
	double  fov_scale;
	double  pixel_x;
	double	pixel_y;
	t_vec3	right;
	t_vec3	up;
	t_vec3	direction;

	// Fix the oval stretching and apply Field of View
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	fov_scale = tan((cam->fov * M_PI / 180.0) / 2.0);

	// Map screen pixels (x, y) to a normalized 3D grid
	pixel_x = (2.0 * ((x + 0.5) / (double)WIDTH) - 1.0) * aspect_ratio * fov_scale;
	pixel_y = (1.0 - 2.0 * ((y + 0.5) / (double)HEIGHT)) * fov_scale;

	// Get the camera's rotation vectors
	get_camera_basis(cam->orientation, &right, &up);

	// Point the ray in the correct direction
	direction = vec3_add(vec3_scale(right, pixel_x), vec3_scale(up, pixel_y));
	direction = vec3_add(direction, cam->orientation);

	return(vec3_normalize(direction));
}

static t_ray	create_camera_ray(t_camera *cam, int x, int y)
{
	t_vec3	direction;

	direction = calculate_direction(cam, x, y);
	return (ray_create(cam->cordinates, direction));
}

static t_vec3	sphere_normal(t_sphere sphere, t_vec3 point)
{
	t_vec3	normal;

	normal = vec3_sub(point, sphere.center);
	normal = vec3_normalize(normal);
	return (normal);
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
