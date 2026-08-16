/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/16 18:34:36 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minirt.h"

static bool	extention_check(char *filename)
{
	int		len;
	char	*trimmed;
	bool	result;

	if (filename == NULL)
		return (false);
	trimmed = ft_strtrim(filename, " \t\n\v\f\r");
	if (trimmed == NULL)
		return (false);
	len = ft_strlen(trimmed);
	result = (len >= 3 && ft_strcmp(trimmed + (len - 3), ".rt") == 0);
	free(trimmed);
	return (result);
}

void	check_args(int ac, char **av)
{
	if (ac != 2 || av == NULL || av[1] == NULL || !extention_check(av[1]))
		error_exit("Error\n", "bad arguments\nexample - ./miniRT file.rt", 1);
}
