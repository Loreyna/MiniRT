#include "../../minirt.h"

bool parse_ambient(t_scene *scene, char **data)
{
	char	**rgb;
	if(ft_count_arrays(data) != 3)
		return (false);
	if(!ft_is_str_double(data[1]))
		return (false);
	scene->ambient->light_ratio = ft_atof(data[1]);
	rgb = ft_split(data[2], ',');
	if(!ft_is_str_numeric(rgb[0]) || !ft_is_str_double(rgb[1]) ||
			!ft_is_str_double(rgb[2]))
			{
				ft_free_matrix((void***)&rgb);
				return (false);
			}

	scene->ambient[0].rgb[0] = ft_atoi(rgb[0]);
	scene->ambient[0].rgb[1] = ft_atoi(rgb[1]);
	scene->ambient[0].rgb[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void***)&rgb);
	return (true);
}
    
bool parse_camera(t_scene *scene, char **data)
{
	char **cord;
	char **norm;
	
	cord = ft_split(data[1], ',');
	if(!ft_is_str_double(cord[0]) || !ft_is_str_double(cord[1]) ||
			!ft_is_str_double(cord[2]))
			{
				ft_free_matrix((void***)&cord);
				return (false);
			}
	scene->cam->cordinates.x = ft_atof(cord[0]);
	scene->cam->cordinates.y = ft_atof(cord[1]);
	scene->cam->cordinates.z = ft_atof(cord[2]);
	norm = ft_split(data[1], ',');
	if(!ft_is_str_double(norm[0]) || !ft_is_str_double(norm[1]) ||
			!ft_is_str_double(norm[2]))
		{
			ft_free_matrix((void***)&norm);
			return (false);
		}
	if(((ft_atof(norm[0]) < -1) && (ft_atof(norm[0]) > 1)) ||
		((ft_atof(norm[1]) < -1) && (ft_atof(norm[1]) > 1))
		|| ((ft_atof(norm[2]) < -1) && (ft_atof(norm[2]) > 1)))
		{
			ft_free_matrix((void***)&norm);
			return (false);
		}
	scene->cam->cordinates.x = ft_atof(norm[0]);
	scene->cam->cordinates.y = ft_atof(norm[1]);
	scene->cam->cordinates.z = ft_atof(norm[2]);
	ft_free_matrix((void***)&norm);
	if(!ft_is_str_numeric(data[3]) || ft_atoi(data[3]) > 180 || ft_atoi(data[3]) < 0)
		return(false);
	scene->cam->fov = ft_atoi(data[3]);
	return(true);
}


