#include "../minirt.h"

bool	extention_check(char *filename)
{
	int len;
	len = ft_strlen(filename);
	if (len < 4)
		return(false);
	if (ft_strcmp(filename + (len - 3), ".rt") == 0)
		return (true);
	return (false);
}

int main(int ac, char **av)
{
	if(ac != 2 || av == NULL || av[1] == NULL || !extention_check(av[1])) 
		error_exit("minirt", "bad arguments\nusage example - ./minirt file.rt\n", 1);	
	ft_printf("Success!\n");
	return(0);
}
