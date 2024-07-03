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
static int case_insensitive_alphanum_compare(const char *s1, const char *s2, bool *isalnum);
static int	alphanum_compare(const char *s1, const char *s2);

int	ls_strcmp(const char *s1, const char *s2)
{
  	int	diff = 0;
	bool	isalnum = false;

	size_t	dots_1 = skip_dots(&s1);
	size_t	dots_2 = skip_dots(&s2);

	diff = case_insensitive_alphanum_compare(s1, s2, &isalnum);
	if (isalnum)
	{
		if (diff == 0)
		{
			diff = alphanum_compare(s1, s2);	
			if (diff == 0)
			{
				diff = ft_strcmp(s1, s2);
				if (diff == 0)
				{
					diff = dots_2 - dots_1;
				}
			}
		}
	}
	else if (diff == 0)
	{
		diff = dots_1 - dots_2;
	}

	return (diff);
}

static int case_insensitive_alphanum_compare(const char *s1, const char *s2, bool *isalnum)
{
	size_t	i = 0;
	size_t	j = 0;

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
		*isalnum = true;
		
		if (ft_toupper(s1[i]) != ft_toupper(s2[j]))
		{
			break;
		}
		++i;
		++j;
	}
	return ((unsigned char)ft_toupper(s1[i]) - (unsigned char)ft_toupper(s2[j]));
}

static int	alphanum_compare(const char *s1, const char *s2)
{
	size_t	i = 0;
	size_t	j = 0;

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
	return ((unsigned int)s2[j] - (unsigned int)s1[i]);
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
