/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:42:12 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/09 09:41:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_move_right(char *dest, const char *src, size_t n);
static void	*ft_move_left(char *dest, const char *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!(dest && src))
		return (dest);
	if (dest > src)
		return (ft_move_right((char *)dest, (char *)src, n));
	else
		return (ft_move_left((char *)dest, (char *)src, n));
}

static void	*ft_move_right(char *dest, const char *src, size_t n)
{
	while (n != 0)
	{
		--n;
		dest[n] = src[n];
	}
	return (dest);
}

static void	*ft_move_left(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		++i;
	}
	return (dest);
}
