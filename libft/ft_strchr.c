/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:42:07 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 10:35:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_target_index(const char *str, unsigned char const target);

char	*ft_strchr(const char *str, int c)
{
	ssize_t	found_index;

	if (str == NULL)
		return (NULL);
	found_index = get_target_index(str, (unsigned char)c);
	if (found_index != -1)
		return ((char *)&str[found_index]);
	else
		return (NULL);
}

static int	get_target_index(const char *str, unsigned char const target)
{
	ssize_t	i;
	ssize_t	found_index;

	found_index = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == target)
		{
			found_index = i;
			break ;
		}
		++i;
	}
	if (target == '\0')
		found_index = i;
	return (found_index);
}
