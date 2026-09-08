/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:12:34 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/08 18:13:26 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_ray	create_camera_ray(t_camera *cam, int x, int y)
{
	t_vec3	direction;

	direction = calculate_direction(cam, x, y);
	return (ray_create(cam->cordinates, direction));
}

t_vec3	calculate_direction(t_camera *cam, int x, int y)
{
	t_camera_ray	ray;

	ray.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	ray.fov_scale = tan((cam->fov * M_PI / 180.0) / 2.0);
	ray.pixel_x = (2.0 * ((x + 0.5) / (double)WIDTH) - 1.0)
		* ray.aspect_ratio * ray.fov_scale;
	ray.pixel_y = (1.0 - 2.0 * ((y + 0.5) / (double)HEIGHT))
		* ray.fov_scale;
	get_camera_basis(cam->orientation, &ray.right, &ray.up);
	ray.direction = vec3_add(vec3_scale(ray.right, ray.pixel_x),
			vec3_scale(ray.up, ray.pixel_y));
	ray.direction = vec3_add(ray.direction, cam->orientation);
	return (vec3_normalize(ray.direction));
}

void	get_camera_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up)
{
	t_vec3	global_up;

	global_up.x = 0;
	global_up.y = 1;
	global_up.z = 0;
	if (fabs(forward.x) < 0.00001 && fabs(forward.z) < 0.00001)
	{
		global_up.y = 0;
		global_up.z = 1;
	}
	*right = vec3_normalize(vec3_cross(global_up, forward));
	*up = vec3_cross(forward, *right);
}
