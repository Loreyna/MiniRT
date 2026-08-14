/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 18:08:04 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/11 18:14:07 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

// Allowed Libraries
#include <math.h>

//Vectors
typedef struct s_vec3
{//double nº con decimales con mas precisión que float
    double x;
    double y;
    double z;
} t_vec3;

t_vec3	vec3_create(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double k);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

//Rays
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

t_vec3 ray_at (t_ray ray, double t);
t_ray ray_create(t_vec3 origin, t_vec3 direction);
#endif
