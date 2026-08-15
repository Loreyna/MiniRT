#ifndef VEC3_H
# define VEC3_H

// Allowed Libraries
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "../libft/libft.h"

//Cordenades
typedef struct s_cord
{
	double x;
	double y;
	double z;
} t_cord;

//Vectors
typedef struct s_vec3
{//double nº con decimales con más precisión que float
	double x;
	double y;
	double z;
} t_vec3;

t_vec3	vec3_create(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double k);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

//Rays
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

t_vec3 ray_at (t_ray ray, double t);
t_ray ray_create(t_vec3 origin, t_vec3 direction);

typedef struct s_hit
{ 
	bool hit;	     //ha chocado?
	double t;	     //distancia hasta el choque?
	t_cord point;	 //Donde ha sido el impacto?
	t_vec3 normal;   //Que direccion tiene la superficie en ese punto?
} t_hit


//Objects
typedef struct s_ambient_l
{
	uint8_t	rgb[3];
	double	light_ratio;
} t_ambient_l;

typedef struct s_camera
{
	t_cord	cordinates;
	t_vec3	orientation;
	uint8_t	fov; 
} t_camera;

typedef struct s_light
{
	t_cord	cordinates;
	double	brightness;
	uint8_t	rgb[3];
} t_light;

typedef struct s_sphere
{
	t_cord	center;
	double	diameter;
	uint8_t	rgb[3];
} t_sphere;

typedef struct s_plane
{
	t_cord	center;
	t_vec3	normal_v;
	uint8_t	rgb[3];
} t_plane;

typedef struct s_cylinder
{
	t_cord	center;
	double	diameter;
	double	height;
	t_vec3	axis_v;
	uint8_t	rgb[3];
} t_cylinder;

//Scene
typedef struct s_scene
{
	int	s_count;
	int	p_count;
	int	cyl_count;

	t_ambient_l	*ambient_l;
	t_camera	*cam;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
} t_scene;
#endif
