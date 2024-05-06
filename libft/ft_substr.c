/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:45 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/23 11:19:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_recompute_len(char const *s, unsigned int start, size_t len);
static void		ft_substr_cpy(char *dest, char const *src, unsigned int start, \
		size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	len = ft_recompute_len(s, start, len);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_substr_cpy(dest, s, start, len);
	return (dest);
}

static	size_t	ft_recompute_len(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;

	str_len = ft_strlen(s);
	if (start + len > str_len)
	{
		len = str_len - start;
	}
	if (start >= str_len)
	{
		len = 0;
	}
	return (len);
}

static void	ft_substr_cpy(char *dest, char const *src, unsigned int start, \
		size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[start + i])
	{
		dest[i] = src[start + i];
			++i;
	}
	dest[i] = '\0';
}
