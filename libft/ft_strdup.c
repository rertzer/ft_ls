/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:51:49 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 10:50:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(src);
  errno = 0;
	dup = malloc(sizeof(char) *(len + 1));
  if (dup == NULL){
        perror("ft_ls: malloc: ");
	}
  else {
	  dup = ft_strcpy(dup, src);
	}
  return (dup);
}
