#include "../minirt.h"

static void	print_scene(t_scene *scene)
{
	printf("Scene:\n");
	printf("  Spheres:		%d\n", scene->s_count);
	printf("  Planes:		%d\n", scene->p_count);
	printf("  Cylinders:	%d\n", scene->cyl_count);
	printf("  Camera:		%d\n", scene->has_camera);
	printf("  Light:		%d\n", scene->has_light);

	printf("  Ambient:		%d\n", scene->has_ambient);
	printf("  Ambient ratio: %.2f\n", scene->ambient[0].light_ratio);
	printf("  Ambient RGB: %d, %d, %d\n",
		scene->ambient[0].rgb[0],
		scene->ambient[0].rgb[1],
		scene->ambient[0].rgb[2]);

	printf("  Camera coordinates: %.2f, %.2f, %.2f\n",
		scene->cam[0].cordinates.x,
		scene->cam[0].cordinates.y,
		scene->cam[0].cordinates.z);
	printf("  Camera orientation: %.2f, %.2f, %.2f\n",
		scene->cam[0].orientation.x,
		scene->cam[0].orientation.y,
		scene->cam[0].orientation.z);
	printf("  Camera FOV: %u\n", scene->cam[0].fov);
}

int main(int ac, char **av)
{
	t_scene	scene;

	check_args(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	allocate_scene(&scene);
	parse_objects(&scene, av[1]);
	print_scene(&scene);
	free_scene(&scene);
	return (0);
}


