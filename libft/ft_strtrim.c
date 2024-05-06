/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:03:51 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/23 10:06:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_start(char const *s1, char const *set);
static size_t	ft_get_end(char const *s1, char const *set);
static size_t	ft_get_len(size_t start, size_t end);
static char		*ft_trim(char const *s1, size_t start, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimed;

	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	len = ft_get_len(start, end);
	trimed = ft_trim(s1, start, len);
	return (trimed);
}

static size_t	ft_get_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] != '\0' && ft_is_inset(s1[start], set))
	{
		++start;
	}
	return (start);
}

static size_t	ft_get_end(char const *s1, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (end != 0 && ft_is_inset(s1[end], set))
	{
		--end;
	}
	return (end);
}

static size_t	ft_get_len(size_t start, size_t end)
{
	size_t	len;

	if (start > end)
		len = 0;
	else
		len = end - start + 1;
	return (len);
}

static char	*ft_trim(char const *s1, size_t start, size_t len)
{
	size_t	i;
	char	*trimed;

	trimed = malloc(sizeof(char) * (len + 1));
	if (trimed == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		trimed[i] = s1[start + i];
		++i;
	}
	trimed[i] = '\0';
	return (trimed);
}
