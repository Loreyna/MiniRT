/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/18 16:10:39 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
/* parsing process:
	check right args count for an object;
	remove '\n' char from the last argument;
	check if each argument is aceptable;
	store the data inside object's struct;*/

bool	parse_init(int argc, char **data)
{
	if (ft_count_arrays(data) != argc)
		return (false);
	remove_nl(data[argc - 1]);
	return (true);
}

static bool	parse_data(t_scene *scene, char **data)
{
	if (ft_strcmp(data[0], "A") == 0)
		parse_ambient(scene, data);
	else if (ft_strcmp(data[0], "C") == 0)
		parse_camera(scene, data);
	else if (ft_strcmp(data[0], "L") == 0)
		parse_light(scene, data);
	return (true);
}

bool	rgb_check(char **rgb)
{
	int	value;
	int	i;

	i = 0;
	while (i < 3)
	{
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (false);
		i++;
	}
	return (true);
}

void	parse_objects(t_scene *scene, char *filename)
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
		if (!parse_data(scene, data))
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
