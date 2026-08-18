/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/18 18:28:48 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

void	free_scene(t_scene *scene)
{
	ft_free((void **)&scene->ambient);
	ft_free((void **)&scene->cam);
	ft_free((void **)&scene->light);
	ft_free((void **)&scene->spheres);
	ft_free((void **)&scene->planes);
	ft_free((void **)&scene->cylinders);
}

static void	check_alloc(void *ptr, bool condition, t_scene *scene)
{
	if (condition && !ptr)
	{
		free_scene(scene);
		error_exit("Error\n", "Bad calloc", 5);
	}
}

static void	check_memory(t_scene *scene)
{
	check_alloc(scene->ambient, scene->has_ambient, scene);
	check_alloc(scene->cam, scene->has_camera, scene);
	check_alloc(scene->light, scene->has_light, scene);
	check_alloc(scene->spheres, scene->s_count, scene);
	check_alloc(scene->planes, scene->p_count, scene);
	check_alloc(scene->cylinders, scene->cyl_count, scene);
}

void	allocate_scene(t_scene *scene)
{
	scene->ambient = ft_calloc(scene->has_ambient, sizeof(t_ambient));
	scene->cam = ft_calloc(scene->has_camera, sizeof(t_camera));
	scene->light = ft_calloc(scene->has_light, sizeof(t_light));
	scene->spheres = ft_calloc(scene->s_count, sizeof(t_sphere));
	scene->planes = ft_calloc(scene->p_count, sizeof(t_plane));
	scene->cylinders = ft_calloc(scene->cyl_count, sizeof(t_cylinder));
	check_memory(scene);
}
