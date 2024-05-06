/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:38:14 by rertzer           #+#    #+#             */
/*   Updated: 2024/02/10 10:50:05 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_size_to_big(size_t nmemb, size_t size)
{
	bool	to_big;

	to_big = false;
	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		to_big = true;
	return (to_big);
}

static void	*set_to_zero(char *mem, size_t mem_size)
{
	size_t	i;

	i = 0;
	while (i < mem_size)
	{
		mem[i] = '\0';
		++i;
	}
	return ((void *)mem);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;

	if (is_size_to_big(nmemb, size))
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	mem = set_to_zero((char *)mem, nmemb * size);
	return (mem);
}
