/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:42:04 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 11:10:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dest;

	len_s1 = ft_strlen(s1);
	
	if (s1[len_s1 - 1] == '/')
	{
		return (ft_strjoin(s1, s2));
	}

	len_s2 = ft_strlen(s2);
	
	errno = 0;
	
	dest = malloc(sizeof(char) *(len_s1 + len_s2 + 2));
	if (NULL == dest)
	{
    	perror("ft_ls: malloc: ");
  	}
	else
	{
		ft_strcpy(dest, s1);
		dest[len_s1]= '/';
		ft_strcpy(&dest[len_s1 + 1], s2);
	}
	
	return (dest);
}
