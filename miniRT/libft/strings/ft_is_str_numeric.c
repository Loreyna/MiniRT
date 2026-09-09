/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/19 17:09:03 by lrey-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_is_str_numeric(char *s)
{
	int	i;

	if (!s || !s[0])
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_str_double(char *s)
{
	int	i;
	int	dot_count;

	dot_count = 0;
	if (!s || !s[0])
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdouble(s[i]))
			return (false);
		if (s[i] == '.')
			dot_count++;
		if (s[i] == '.' && (s[i + 1] == '\0'))
			return (false);
		i++;
	}
	if (dot_count != 0 && dot_count != 1)
		return (false);
	return (true);
}
