/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:34:25 by rertzer           #+#    #+#             */
/*   Updated: 2024/06/06 14:39:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathdup(const char *src)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(src);
 	errno = 0;
	dup = malloc(sizeof(char) *(len + 1));
 	if (dup == NULL)
	{
		perror("ft_ls: malloc: ");
	}
	else
	{
		size_t	i;

		i = 0;
		while (src[i] != '\0')
		{
			dup[i] = src[i];
			++i;
		}
		while (i > 2 && dup[i - 1] == '/')
		{
			--i;
		}

		dup[i] = '\0';
	}
	return (dup);
}
