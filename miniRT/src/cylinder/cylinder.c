/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:19:12 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/04 17:58:40 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec3 cylinder_normal(t_vec3 hit_point, t_cylinder cylinder)
{
	t_vec3 normal;
	t_vec3 to_hit;
	double projection;

	cylinder.axis_v = vec3_normalize(cylinder.axis_v);
	to_hit = vec3_sub(hit_point, cylinder.center);
	projection =  vec3_dot(to_hit, cylinder.axis_v);
	normal = vec3_sub(to_hit,vec3_scale(cylinder.axis_v, projection));
	
	return (vec3_normalize(normal));
	
}

/*static bool get_closest_t(t_quadratic q, double *t)
{
	if (q.t1 > 0 && q.t2 > 0)
	{
    	if (q.t1 < q.t2)
        	*t = q.t1;
    	else
        	*t = q.t2;
	}	
	else if (q.t1 > 0)
    	*t = q.t1;
	else if (q.t2 > 0)
    	*t = q.t2;
	else
    	return (false);
	return (true);
}

static bool calculate_hit (t_ray ray, t_cylinder cylinder, double *t)
{
	t_vec3 hit_point;
	t_vec3 hit_to_center;
	double height;
	
	hit_point = ray_at(ray, *t);
	hit_to_center = vec3_sub(hit_point, cylinder.center);
	height = vec3_dot(hit_to_center, cylinder.axis_v);
	
	if( height > cylinder.height / 2 )
		return (false);
	else if( height < -cylinder.height / 2)
		return (false);
	return (true);
}*/

static bool validate_hit_height(t_ray ray, t_cylinder cylinder, double t, double *out_t)
{
    t_vec3 hit_point = ray_at(ray, t);
    t_vec3 hit_to_center = vec3_sub(hit_point, cylinder.center);
    double height = vec3_dot(hit_to_center, cylinder.axis_v);

    if (height >= -cylinder.height / 2 && height <= cylinder.height / 2)
    {
        *out_t = t;
        return (true);
    }
    return (false);
}
bool is_cylinder_hit(t_ray ray, t_cylinder cylinder, double *t)
{ 
	t_quadratic q;
	double dot_dir_axis;
	double dot_oc_axis;
	
	cylinder.axis_v = vec3_normalize(cylinder.axis_v);
	q.oc = vec3_sub(ray.origin, cylinder.center);// vector desde el punto de la cylinder al origen del rayo 
	dot_dir_axis = vec3_dot(ray.direction, cylinder.axis_v);//(direccion · eje)
	q.a = vec3_dot( ray.direction, ray.direction) - (dot_dir_axis * dot_dir_axis);
	if (fabs(q.a) < 0.000001) 
		return (false); 
	dot_oc_axis = vec3_dot(q.oc, cylinder.axis_v);//(oc · eje)
	q.b = 2.0 * ((vec3_dot(q.oc, ray.direction)) - (dot_oc_axis * dot_dir_axis));
	q.radius = cylinder.diameter / 2;
	q.c = vec3_dot(q.oc, q.oc) - (dot_oc_axis * dot_oc_axis) - (q.radius * q.radius);
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;//resultado de lo que hay dentro de la raiz cuadrada
	if (q.discriminant < 0)// no choca 
		return (false); 
/*	if(!get_closest_t(q, t))
		return (false);
	if (!calculate_hit(ray, cylinder, t))
	return (false);

	return (true);*/
	double sqrt_d = sqrt(q.discriminant);
        double t1 = (-q.b - sqrt_d) / (2.0 * q.a);
        double t2 = (-q.b + sqrt_d) / (2.0 * q.a);
        if (t1 > t2) 
        {
                double temp = t1;
                t1 = t2;
                t2 = temp;
        }
        if (t1 > 0 && validate_hit_height(ray, cylinder, t1, t))
                return (true);

        if (t2 > 0 && validate_hit_height(ray, cylinder, t2, t))
                return (true);
 
        return (false);
}

/*
a = (dirección · dirección) - (dirección · eje)²
b = 2 * ((oc · dirección) - (oc · eje) * (dirección · eje))
c = (oc · oc) - (oc · eje)² - radio²

*/
