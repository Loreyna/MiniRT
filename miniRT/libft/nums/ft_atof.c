#include "../libft.h"

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	char	*copy;
	int		count = 1;
	
	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str++ - '0');
	}
	if(*str == '.')
	{
		copy = str;
		str++;
		copy++;
		while(ft_isdigit(*copy))
		{
			count = count * 10;
			copy++;
		}
	}
		while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str++ - '0');
	}
	return ((result * sign) / count);
}
