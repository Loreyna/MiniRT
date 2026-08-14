/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cec3_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:18:57 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/07/31 13:28:25 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	t_vec3 vec3;
	double n;
	vec3.x = a.x * b.x;
	vec3.y = a.y * b.y;
	vec3.z = a.z * b.z;
	n = vec3.x + vec3.y + vec3.z;
	return (n);
}

/*
n =
positivo -> apuntan mas o menos en la misma dirección.
cero -> son perpendiculares (90°).
negativo -> apuntan en direcciones opuestas.
*/
