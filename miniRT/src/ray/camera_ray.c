/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:12:34 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 17:13:40 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_ray	create_camera_ray(t_camera *cam, int x, int y)
{
	t_vec3	direction;

	direction = calculate_direction(cam, x, y);
	return (ray_create(cam->cordinates, direction));
}

t_vec3 calculate_direction(t_camera *cam, int x, int y)
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

void get_camera_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up)
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