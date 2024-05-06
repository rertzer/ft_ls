/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:12:46 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/02 11:02:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*uchar_s;

	if (s == NULL)
		return (NULL);
	i = 0;
	uchar_s = (unsigned char *)s;
	while (uchar_s[i] != (unsigned char)c && i < n)
	{
		++i;
	}
	if (i == n)
		return (NULL);
	return (&uchar_s[i]);
}
