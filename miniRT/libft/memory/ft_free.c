/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:31:28 by jgalizio          #+#    #+#             */
/*   Updated: 2026/08/16 15:54:23 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* Takes a &pointer to free it and sends it to NULL*/
void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
