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
	size_t	j = 0;
	bool	isalnum = false;

		a = ft_toupper(s1[i]);
		b = ft_toupper(s2[j]);
	while (s1[i] != '\0' && s2[j] != '\0')
	{ 
		if (! ft_isalnum(s1[i]))
		{
			++i;
			a = ft_toupper(s1[i]);
			continue;
		}
		if (! ft_isalnum(s2[j]))
		{
			++j;
			b = ft_toupper(s2[j]);
			continue;
		}
		isalnum = true;
		
		if (a != b)
		  break;
		++i;
		++j;
		a = ft_toupper(s1[i]);
		b = ft_toupper(s2[j]);
	}
	if (isalnum)
	{
		if (s1[i] == '\0' && s2[j] == '\0')
		{
			i = 0;
			j = 0;
			while (s1[i] != '\0' && s2[j] != '\0')
			{
				if (! ft_isalnum(s1[i]))
				{
					++i;
					continue;
				}
				if (! ft_isalnum(s2[j]))
				{
					++j;
					continue;
				}

				if (s1[i] != s2[j])
					break;
				++i;
				++j;
			}
			diff = s2[j] - s1[i];
			if (diff == 0)
			{
				i = 0;
				j = 0;
				while (s1[i] != '\0' && s2[j] != '\0')
				{
					
					if (s1[i] != s2[j])
						break;
					++i;
					++j;
				}
				diff = (unsigned int)s1[i] - (unsigned int)s2[j];
			}
		}
		else
		{
			diff = (unsigned char)a - (unsigned char)b;
		}
		if (diff == 0)
		{
			diff = dots_2 - dots_1;
		}
	}
	else
		{
			if (a == '\0' && b == '\0')
				diff = dots_1 - dots_2;
			else
				diff = (unsigned char)a - (unsigned char)b;
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
	if (i != 0 )//&& (*s)[i] != '\0')
	{
		*s = &(*s)[i];
	}
	return (i);
}
