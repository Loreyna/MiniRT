#include "../minirt.h"

static void	print_scene(t_scene *scene)
{
	printf("Scene:\n");
	printf("  Spheres:   %d\n", scene->s_count);
	printf("  Planes:    %d\n", scene->p_count);
	printf("  Cylinders: %d\n", scene->cyl_count);
	printf("  Spheres:   %d\n", scene->has_ambient);
	printf("  Planes:    %d\n", scene->has_camera);
	printf("  Cylinders: %d\n", scene->has_light);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	check_args(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	print_scene(&scene);
	allocate_scene(&scene);
	free_scene(&scene);
	return (0);
}
