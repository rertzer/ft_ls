/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:58:12 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 11:36:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_smallest(size_t a, size_t b);

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (!(src && size))
		return (len);
	size = get_smallest(size - 1, len);
	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (len);
}

static size_t	get_smallest(size_t a, size_t b)
{
	size_t	smallest;

	if (a < b)
		smallest = a;
	else
		smallest = b;
	return (smallest);
}
