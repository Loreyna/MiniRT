/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_nl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:57:22 by viaremko          #+#    #+#             */
/*   Updated: 2026/08/18 14:38:52 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void remove_nl(char *str)
{
	int	len;
	
	if(!str)
		return;
	len = ft_strlen(str);
 	if (len > 0 && str[len - 1] == '\n')
        	str[len - 1] = '\0';
}
