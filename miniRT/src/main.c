/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 19:45:38 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/09/08 19:45:42 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	main(int ac, char **av)
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	check_args(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	allocate_scene(&scene);
	parse_objects(&scene, av[1]);
	mlx = create_window(HEIGHT, WIDTH);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (scene.has_camera)
		render_scene(&scene, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &escape_cfg, mlx);
	mlx_loop(mlx);
	free_scene(&scene);
	mlx_terminate(mlx);
	return (0);
}
