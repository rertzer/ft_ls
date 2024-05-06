/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:31:19 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 11:56:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	are_strings_identical(const char *big, const char *little);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		little_len;

	if ((little == NULL) || (little[0] == '\0'))
		return ((char *)big);
	if (len == 0)
		return (NULL);
	little_len = ft_strlen(little);
	i = 0;
	while ((big[i] != '\0') && (i < len - little_len + 1))
	{
		if (are_strings_identical(&big[i], little) == true)
			return ((char *)&big[i]);
		++i;
	}
	return (NULL);
}

static bool	are_strings_identical(const char *big, const char *little)
{
	size_t	i;
	bool	identical;

	identical = false;
	i = 0;
	while (big[i] != '\0' && big[i] == little[i])
	{
		++i;
	}
	if (little[i] == '\0')
		identical = true;
	return (identical);
}
