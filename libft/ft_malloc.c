/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:50:17 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/15 09:50:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	errno = 0;
	void	*ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("ft_ls: malloc: ");
	}
	return (ptr);
}
