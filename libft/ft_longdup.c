/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:21:09 by rertzer           #+#    #+#             */
/*   Updated: 2024/06/10 14:22:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* !! buffer must be 8 aligned !! */

#include "libft.h"

char	*ft_longdup(const void *src)
{
	int		long_len;
	long	*long_src = (long*)src;
	long	*long_dup;

	int	len = ft_strlen((char*)src) + 1;
	
	int	r = len % 8;
	long_len = len / 8;
	if (r != 0)
	{
		long_len += 1;
	}
	
	errno = 0;
	long_dup = malloc(sizeof(long) *(long_len));
	if (long_dup == NULL)
	{
        perror("ft_ls: malloc: ");
	}
  	else
	{
		for (int i = 0 ; i < long_len; ++i)
		{
			long_dup[i] = long_src[i];
		}
	}
	
	char *dup = (char*)long_dup;
	dup[len - 1] = '\0';
	
	return (dup);
}

