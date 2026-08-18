/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrey-mol <lrey-mol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:14 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/18 13:16:11 by viaremko         ###   ########.fr       */
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
		i++;
	}
	return (true);
}
