/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:58:28 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 11:43:48 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_ci(const char *s1, const char *s2)
{
	size_t	i;
  char  a;
  char  b;

	i = 0;
	while (s1[i] != '\0')
	{ 
    a = ft_toupper(s1[i]);
    b = ft_toupper(s2[i]);
    
    if (a != b)
      break;
		++i;
	}
	return ((unsigned char)a - (unsigned char)b);
}
