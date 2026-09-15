/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/09/03 19:07:22 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minirt.h"

bool	ft_is_null(char *str)
{
	if (!str)
		return (false);
	return (ft_strcmp(str, "null") == 0);
}

bool	validate_coords(char **cord)
{
	if (!cord || !cord[0] || !cord[1] || !cord[2])
		return (false);
	if ((!ft_is_str_double(cord[0]) && !ft_is_null(cord[0]))
		|| (!ft_is_str_double(cord[1]) && !ft_is_null(cord[1]))
		|| (!ft_is_str_double(cord[2]) && !ft_is_null(cord[2])))
	{
		return (false);
	}
	return (true);
}

double	get_coord_val(char *str)
{
	if (ft_is_null(str))
		return (0.0);
	return (ft_atof(str));
}
