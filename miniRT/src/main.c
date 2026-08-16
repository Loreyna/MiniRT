#include "../minirt.h"

static void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
}

static void	print_scene(t_scene *scene)
{
	printf("Scene:\n");
	printf("  Spheres:   %d\n", scene->s_count);
	printf("  Planes:    %d\n", scene->p_count);
	printf("  Cylinders: %d\n", scene->cyl_count);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	args_check(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	print_scene(&scene);
	return (0);
}
