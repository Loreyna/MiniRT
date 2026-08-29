/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 17:27:50 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 17:35:25 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool is_plane_hit(t_ray ray, t_plane plane, double *t)//¿este rayo toca a este plano?
{
	t_vec3 vector;
	double numerator;
	double denominator;
	
	vector = vec3_sub(plane.point, ray.origin);//(Po​−O)...
	numerator = vec3_dot(vector, plane.normal_v); // ...·N
	denominator = vec3_dot(ray.direction, plane.normal_v);// D·N
	if (fabs(denominator) < 0.000001)//si esta lo suficientemente cerca de cero, no toca.
		return (false);
	*t = numerator / denominator;
	if(*t < 0.000001)
		return (false);
	return (true);
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







/*
t=(Po​−O)⋅N​ / D·N
Po, centro del plano
O, origen del rayo
N normal
D ray Direction
*/