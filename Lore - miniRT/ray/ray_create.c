/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 18:17:59 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/11 18:39:13 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray new_ray;
	
	new_ray.origin = origin;
	new_ray.direction = direction;
	return (new_ray);
}
