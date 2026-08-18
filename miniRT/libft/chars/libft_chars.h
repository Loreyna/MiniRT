/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_chars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:23:12 by jgalizio          #+#    #+#             */
/*   Updated: 2026/08/18 15:28:01 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHARS_H
# define LIBFT_CHARS_H

# include "../libft_incs.h"

int	ft_isascii(int c);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isdouble(char c);
int	ft_isprint(int c);
int	ft_isalnum(int c);
int	ft_isspace(int c);
int	ft_tolower(int c);
int	ft_toupper(int c);

#endif
