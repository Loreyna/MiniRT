/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 13:43:44 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/15 15:47:37 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_vec3	vec3_normalize(t_vec3 v)
{
	t_vec3	vec3;
	double	n;

	n = vec3_length(v);
	vec3.x = v.x / n;
	vec3.y = v.y / n;
	vec3.z = v.z / n;
	return (vec3);
}
