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
static int				case_insensitive_alphanum_compare(const char *s1, const char *s2, bool *isalnum);
static int				alphanum_compare(const char *s1, const char *s2);
static bool				get_compare_offset(const char *s1, const char *s2, size_t *i, size_t *j, int (*case_modifier)(int));
static inline int 		to_itself(int c);

int	ls_strcmp(const char *s1, const char *s2)
{
  	int		diff = 0;
	bool	is_alnum = false;

	size_t	dots_1 = skip_dots(&s1);
	size_t	dots_2 = skip_dots(&s2);

	diff = case_insensitive_alphanum_compare(s1, s2, &is_alnum);
	if (is_alnum)
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

static int case_insensitive_alphanum_compare(const char *s1, const char *s2, bool *is_alnum)
{
	size_t	i = 0;
	size_t	j = 0;

	*is_alnum = get_compare_offset(s1, s2, &i, &j, ft_toupper);
	return ((unsigned char)ft_toupper(s1[i]) - (unsigned char)ft_toupper(s2[j]));
}

static int	alphanum_compare(const char *s1, const char *s2)
{
	size_t	i = 0;
	size_t	j = 0;

	get_compare_offset(s1, s2, &i, &j, to_itself);

	return ((unsigned int)s2[j] - (unsigned int)s1[i]);
}

static bool	get_compare_offset(const char *s1, const char *s2, size_t *i, size_t *j, int (*case_modifier)(int))
{
	bool	is_alnum = false;

	while (s1[*i] != '\0' && s2[*j] != '\0')
	{ 
		if (! ft_isalnum(s1[*i]))
		{
			++(*i);
			continue;
		}
		if (! ft_isalnum(s2[*j]))
		{
			++(*j);
			continue;
		}
		is_alnum = true;
		
		if (case_modifier(s1[*i]) != case_modifier(s2[*j]))
		{
			break;
		}
		++(*i);
		++(*j);
	}

	return (is_alnum);
}

static inline int to_itself(int c)
{
	return (c);
}

static inline size_t	skip_dots(const char **s)
{
	size_t	i = 0;

	while ((*s)[i] == '.')
	{
		++i;
	}
	if (i != 0 )
	{
		*s = &(*s)[i];
	}
	return (i);
}
