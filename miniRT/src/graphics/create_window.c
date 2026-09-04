/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/09/04 17:54:21 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

mlx_t	*create_window(int height, int width)
{
	mlx_t	*mlx;

	mlx = mlx_init(height, width, "miniRT", true);
	if (!mlx)
		error_exit("Error\n", "Bad mlx initialization", 99);
	return (mlx);
}
