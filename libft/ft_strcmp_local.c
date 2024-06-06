/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_local.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:29:19 by rertzer           #+#    #+#             */
/*   Updated: 2024/06/06 09:29:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline bool	is_dot_file(const char *s);

int	ft_strcmp_local(const char *s1, const char *s2)
{
	size_t	i;
  char  a;
  char  b;

	i = 0;
	if (is_dot_file(s1))
	{
		++s1;
	}
	if (is_dot_file(s2))
	{
		++s2;
	}

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

static inline bool	is_dot_file(const char *s)
{
	return (*s == '.' && ft_strcmp(s, ".") && ft_strcmp(s, ".."));
}
