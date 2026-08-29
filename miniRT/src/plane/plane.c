/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 17:27:50 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 18:08:16 by lrey-mol         ###   ########.fr       */
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









/*
t=(Po​−O)⋅N​ / D·N
Po, centro del plano
O, origen del rayo
N normal
D ray Direction
*/