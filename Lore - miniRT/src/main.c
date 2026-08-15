#include "../minirt.h"


static	bool	extention_check(char *filename)
{
	int len;
	char *trimmed;
	bool result;

	if (filename == NULL)
		return (false);
	trimmed = ft_strtrim(filename, " \t\n\v\f\r");
	if (trimmed == NULL)
		return (false);
	len = ft_strlen(trimmed);
	result = (len >= 3 && ft_strcmp(trimmed + (len - 3), ".rt") == 0);
	free(trimmed);	
	return (result);
}

static	void	args_check(int ac, char **av)
{
	if(ac != 2 || av == NULL || av[1] == NULL || !extention_check(av[1])) 
		error_exit("minirt", "bad arguments\nusage example - ./minirt file.rt", 1);
}

static	bool	process_data(t_scene *scene, char **data)
{
	static bool	has_camera;
	static bool	has_ambient;
	static bool	has_light;

	if(!data || !data[0]) 
		return(false);
	if(ft_strcmp("\n", data[0]) == 0)
		return (true);
	
	if(ft_strcmp("A", data[0]) == 0)
	{
		if(has_ambient)
			return (false);
		has_ambient = true;
	}
	else if(ft_strcmp("C", data[0]) == 0)
	{
		if(has_camera)
			return (false);
		has_camera = true;
	}
	else if(ft_strcmp("L", data[0]) == 0)
	{
		if(has_light)
			return (false);
		has_light = true;
	}
	else if(ft_strcmp("sp", data[0])== 0)
		scene->s_count++;
	else if(ft_strcmp("pl", data[0]) == 0)
		scene->p_count++;
	else if(ft_strcmp("cy", data[0]) == 0)
		scene->cyl_count++;
	else 
		return (false);
	return (true);
}


static	void	count_objects(t_scene *scene, char *filename)
{
	int	fd;
	char	*line;
	char	**data;

	fd = open(filename, O_RDONLY);
	if(fd == -1)			
		error_exit("minirt", "can't open file, bad file descriptor.", 2);

	while((line = get_next_line(fd)) != NULL)
	{
		data = ft_split(line, ' ');
		if(!process_data(scene, data))
		{
			ft_free((void **)&line);
			ft_free_matrix((void ***)&data);
			error_exit("minirt","bad data.",3);
		}
		ft_free((void **)&line); //here it bugs
		ft_free_matrix((void ***)&data);
	}
}



static	void init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

static	void	print_scene(t_scene *scene)
{
	printf("Scene:\n");
	printf("  Spheres:   %d\n", scene->s_count);
	printf("  Planes:    %d\n", scene->p_count);
	printf("  Cylinders: %d\n", scene->cyl_count);
}

int main(int ac, char **av)
{
	t_scene	scene;

	args_check(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	print_scene(&scene);
	
	return(0);
}
