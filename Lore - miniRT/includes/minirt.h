

#ifndef VEC3_H
# define VEC3_H

// Allowed Libraries
#include <math.h>
#include <stdint.h>

//Objects
typedef struct s_ambient_l
{
	uint8_t	rgb[3];
	float	light_ratio;
} t_ambient_l;

typedef struct s_camera
{
	float	cordinates[3];
	t_vec3	orientation;
	uint8_t	fov; 
} t_camera;

typedef struct s_light
{
	float	cordinates[3];
	float	brightness;
	uint8_t	rgb[3];
} t_light;

typedef struct s_sphere
{
	float	cordinates[3];
	float	diameter;
	uint8_t	rgb[3];
} t_sphere;

typedef struct s_plane
{
	float	cordinates[3];
	t_vec3	normal_v;
	uint8_t	rgb[3];
} t_plane;

typedef struct s_cylinder
{
	float	cordinates[3];
	float	diameter;
	float	height;
	t_vec3	axis_v;
	uint8_t	rgb[3];
} t_cylinder;

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

#endif
