/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:35:48 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/07/31 13:49:01 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	vec3_length(t_vec3 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/*
Devuelve la longitud del vector, es decir, cuánto mide.
*/