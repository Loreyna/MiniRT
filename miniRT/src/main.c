#include "../minirt.h"

static void	print_scene(t_scene *scene)
{
	printf("Scene:\n");
	printf("  Spheres:		%d\n", scene->s_count);
	printf("  Planes:		%d\n", scene->p_count);
	printf("  Cylinders:	%d\n", scene->cyl_count);
	printf("  Ambient:		%d\n", scene->has_ambient);
	printf("  Camera:		%d\n", scene->has_camera);
	printf("  Light:		%d\n", scene->has_light);

	if(scene->has_ambient == 1)
	{
		printf("  Ambient ratio: %.2f\n", scene->ambient[0].light_ratio);
		printf("  Ambient RGB: %d, %d, %d\n",
			scene->ambient[0].rgb[0],
			scene->ambient[0].rgb[1],
			scene->ambient[0].rgb[2]);
	}

	if(scene->has_camera == 1)
	{
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
	if(scene->has_light == 1)
	{
		printf("  Light coordinates: %.2f, %.2f, %.2f\n",
			scene->light->cordinates.x,
			scene->light->cordinates.y,
			scene->light->cordinates.z);
		printf("  Light brightness: %.2f\n",
			scene->light->brightness);
		printf("  Light RGB: %d, %d, %d\n",
    		scene->light->rgb[0],
    		scene->light->rgb[1],
    		scene->light->rgb[2]);
	}
	if (scene->s_count >= 1)
	{
		int i;

		i = 0;
		while (i < scene->s_count)
		{
			printf("\tSphere %d:\n", i + 1);
			printf("\t\tCenter: %.2f, %.2f, %.2f\n",
				scene->spheres[i].center.x,
				scene->spheres[i].center.y,
				scene->spheres[i].center.z);
			printf("\t\tDiameter: %.2f\n",
				scene->spheres[i].diameter);
			printf("\t\tRGB: %d, %d, %d\n",
				scene->spheres[i].rgb[0],
				scene->spheres[i].rgb[1],
				scene->spheres[i].rgb[2]);
			i++;
		}
	}
	if (scene->p_count >= 1)
	{
		int i;

		i = 0;
		while (i < scene->p_count)
		{
			printf("\tPlane %d:\n", i + 1);
			printf("\t\tCenter: %.2f, %.2f, %.2f\n",
				scene->planes[i].point.x,
				scene->planes[i].point.y,
				scene->planes[i].point.z);
			printf("\t\tNormal: %.2f, %.2f, %.2f\n",
				scene->planes[i].normal_v.x,
				scene->planes[i].normal_v.y,
				scene->planes[i].normal_v.z);
			printf("\t\tRGB: %d, %d, %d\n",
				scene->planes[i].rgb[0],
				scene->planes[i].rgb[1],
				scene->planes[i].rgb[2]);
			i++;
		}
	}
	if (scene->cyl_count >= 1)
	{
		int i;

		i = 0;
		while (i < scene->cyl_count)
		{
			printf("\tCylinder %d:\n", i + 1);
			printf("\t\tCenter: %.2f, %.2f, %.2f\n",
				scene->cylinders[i].center.x,
				scene->cylinders[i].center.y,
				scene->cylinders[i].center.z);
			printf("\t\tDiameter: %.2f\n",
				scene->cylinders[i].diameter);
			printf("\t\tHeight: %.2f\n",
				scene->cylinders[i].height);
			printf("\t\tAxis: %.2f, %.2f, %.2f\n",
				scene->cylinders[i].axis_v.x,
				scene->cylinders[i].axis_v.y,
				scene->cylinders[i].axis_v.z);
			printf("\t\tRGB: %d, %d, %d\n",
				scene->cylinders[i].rgb[0],
				scene->cylinders[i].rgb[1],
				scene->cylinders[i].rgb[2]);
			i++;
		}
	}
}

int main(int ac, char **av)
{
	t_scene	scene;
	mlx_t	*mlx;
	mlx_image_t	*img;

	check_args(ac, av);
	init_scene(&scene);
	count_objects(&scene, av[1]);
	allocate_scene(&scene);
	parse_objects(&scene, av[1]);
	print_scene(&scene);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if(!mlx)
		error_exit("Error\n", "Bad mlx initialization", 99);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if(scene.has_camera)
		render_scene(&scene, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, &escape_cfg, mlx);
	mlx_loop(mlx);
	free_scene(&scene);
	mlx_terminate(mlx);
	return (0);
}
