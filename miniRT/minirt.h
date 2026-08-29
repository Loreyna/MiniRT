/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 16:46:31 by lrey-mol          #+#    #+#             */
/*   Updated: 2026/08/29 18:45:05 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// Allowed Libraries
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <unistd.h>
#define WIDTH 900
#define HEIGHT 900



typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	t_quadratic;

// Vectors
typedef struct s_vec3
{
// double nº con decimales con más precisión que float
	double		x;
	double		y;
	double		z;
}				t_vec3;

t_vec3			vec3_create(double x, double y, double z);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_scale(t_vec3 v, double k);
double			vec3_dot(t_vec3 a, t_vec3 b);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
double			vec3_length(t_vec3 v);
t_vec3			vec3_normalize(t_vec3 v);

// Rays
typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

t_vec3			ray_at(t_ray ray, double t);
t_ray			ray_create(t_vec3 origin, t_vec3 direction);
// Objects
typedef struct s_ambient
{
	double		light_ratio;
	uint8_t		rgb[3];
}				t_ambient;

typedef struct s_camera
{
	t_vec3		cordinates;
	t_vec3		orientation;
	uint8_t		fov;
}				t_camera;

typedef struct s_light
{
	t_vec3		cordinates;
	double		brightness;
	uint8_t		rgb[3];
}				t_light;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	uint8_t		rgb[3];
	t_quadratic	q;
}				t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal_v;
	uint8_t		rgb[3];
}				t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	double		diameter;
	double		height;
	t_vec3		axis_v;
	uint8_t		rgb[3];
}				t_cylinder;

// Scene
typedef struct s_scene
{
	bool		has_ambient;
	bool		has_camera;
	bool		has_light;
	int			s_count;
	int			s_index;
	int			p_count;
	int			p_index;
	int			cyl_count;
	int			cyl_index;

	t_ambient	*ambient;
	t_camera	*cam;
	t_light		*light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}				t_scene;

typedef struct s_hit
{
	bool		hit;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
}	t_hit;

// Memory
void	init_scene(t_scene *scene);
void	free_scene(t_scene *scene);
void	allocate_scene(t_scene *scene);

// Parser
bool	parse_init(int argc, char **data);
void	check_args(int ac, char **av);
bool	rgb_check(char **rgb);
void	count_objects(t_scene *scene, char *filename);
void	parse_objects(t_scene *scene, char *filename);
bool	parse_ambient(t_scene *scene, char **data);
bool	parse_camera(t_scene *scene, char **data);
bool	parse_light(t_scene *scene, char **data);
bool	parse_sphere(t_scene *scene, char **data);
bool	parse_plane(t_scene *scene, char **data);
bool	parse_cylinder(t_scene *scene, char **data);

// Render
void	render_sphere (t_scene *scene, mlx_image_t *img);

//Lighting
double calculate_diffuse(t_vec3 hit_point, t_vec3 normal, t_light *light);

// Graphics
mlx_t	*create_window(int height, int width);

// Utils
uint32_t	rgb_to_hex(uint8_t rgb[3]);

//Ray
t_ray	create_camera_ray(t_camera *cam, int x, int y);
t_vec3 calculate_direction(t_camera *cam, int x, int y);
void get_camera_basis(t_vec3 forward, t_vec3 *right, t_vec3 *up);

//plane
void render_plane (t_scene *scene, mlx_image_t *img);
bool is_plane_hit(t_ray ray, t_plane plane, double *t);


//Esphere
bool		is_sphere_hit(t_ray ray, t_sphere sphere, double *t);
bool		find_closest_sphere(t_scene *scene, t_ray ray, double *closest_t, int *index);
t_vec3		sphere_normal(t_sphere sphere, t_vec3 point);
//uint32_t 	calculate_lighting(t_scene *scene, t_hit hit);



#endif
