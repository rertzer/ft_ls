/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:59:59 by rertzer           #+#    #+#             */
/*   Updated: 2024/06/06 10:00:02 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

static inline size_t	skip_dots(const char **s);

int	ls_strcmp(const char *s1, const char *s2)
{
  	int	diff = 0;

	size_t	dots_1 = skip_dots(&s1);
	size_t	dots_2 = skip_dots(&s2);
	char	a = 0;
	char	b = 0;
	size_t	i = 0;

	while (s1[i] != '\0')
	{ 
		a = ft_toupper(s1[i]);
		b = ft_toupper(s2[i]);
		
		if (a != b)
		  break;
		++i;
	}

	if (s1[i] == '\0' && s2[i] == '\0')
	{
		i = 0;
		while (s1[i] != '\0')
		{
			if (s1[i] != s2[i])
				break;
			++i;
		}
		diff = s2[i] - s1[i];
	}
	else
	{
		diff = (unsigned char)a - (unsigned char)b;
	}
	if (diff == 0)
	{
		diff = dots_2 - dots_1;
	}
	return (diff);
}

static inline size_t	skip_dots(const char **s)
{
	size_t	i = 0;

	while ((*s)[i] == '.')
	{
		++i;
	}
	if (i != 0 && (*s)[i] != '\0')
	{
		*s = &(*s)[i];
	}
	return (i);
}
