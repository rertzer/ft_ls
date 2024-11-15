/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:31:34 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/09 09:43:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*cset;
	char		cc = (char)c;

	cset = (char *)s;
	i = 0;
	while (i < n)
	{
		cset[i] = cc;
		++i;
	}
	return (s);
}
