/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/16 18:50:09 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minirt.h"

static bool	check_unique(bool *found)
{
	if (*found)
		return (false);
	*found = true;
	return (true);
}

static bool	check_objects(t_scene *scene, char **data)
{
	if (ft_strcmp("A", data[0]) == 0)
		return (check_unique(&scene->has_ambient));
	else if (ft_strcmp("C", data[0]) == 0)
		return (check_unique(&scene->has_camera));
	else if (ft_strcmp("L", data[0]) == 0)
		return (check_unique(&scene->has_light));
	return (false);
}

static bool	check_figures(t_scene *scene, char **data)
{
	if (ft_strcmp("sp", data[0]) == 0)
	{
		scene->s_count++;
		return (true);
	}
	else if (ft_strcmp("pl", data[0]) == 0)
	{
		scene->p_count++;
		return (true);
	}
	else if (ft_strcmp("cy", data[0]) == 0)
	{
		scene->cyl_count++;
		return (true);
	}
	return (false);
}

static bool	count_data(t_scene *scene, char **data)
{
	if (!data || !data[0])
		return (false);
	if (ft_strcmp("\n", data[0]) == 0)
		return (true);
	if (!check_objects(scene, data) && !check_figures(scene, data))
		return (false);
	return (true);
}

void	count_objects(t_scene *scene, char *filename)
{
	int		fd;
	char	*line;
	char	**data;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Error\n", "can't open file, bad file descriptor.", 2);
	line = get_next_line(fd);
	while (line != NULL)
	{
		data = ft_split(line, ' ');
		if (!count_data(scene, data))
		{
			ft_free((void **)&line);
			ft_free_matrix((void ***)&data);
			error_exit("Error\n", "bad data.", 3);
		}
		ft_free((void **)&line);
		ft_free_matrix((void ***)&data);
		line = get_next_line(fd);
	}
}
