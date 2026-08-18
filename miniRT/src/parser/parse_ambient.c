#include "../../minirt.h"

static bool parse_light_ratio(t_scene *scene, char **data)
{
	if(!ft_is_str_double(data[1]))
		return (false);
	scene->ambient->light_ratio = ft_atof(data[1]);
	return (true);
}

static bool parse_rgb(t_scene *scene, char **data)
{
	char	**rgb;

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

bool parse_ambient(t_scene *scene, char **data)
{
	if(!parse_init(3, data))
		return (false);
	if(!parse_light_ratio(scene, data))
		return(false);
	if(!parse_rgb(scene, data))
		return(false);
	return (true);
}

