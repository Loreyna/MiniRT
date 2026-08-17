#include "../../minirt.h"

static bool parse_data(t_scene *scene, char **data)
{
	if (ft_strcmp(data[0], "A") == 0)
		parse_ambient(scene, data);
	else if(ft_strcmp(data[0], "C") == 0)
		parse_camera(scene, data);
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