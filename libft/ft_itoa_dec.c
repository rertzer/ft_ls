/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:44:16 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/11 12:45:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*chop_nbr_dec(char *buffer, size_t nb, size_t len)
{
	char	base[17] = "0123456789";
	while (nb / 10)
	{
		--len;
		buffer[len] = base[nb % 10];
		nb = nb / 10;
	}
	buffer[len - 1] = base[nb % 10];
	return (buffer);
}

static size_t	ft_getlen_dec(size_t nb)
{
	size_t	len;

	len = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		++len;
	}
	return (len);
}

size_t	ft_itoa_dec(size_t nb, char *buffer)
{
	size_t	len;

	len = ft_getlen_dec(nb);
	buffer[len] = '\0';
	(chop_nbr_dec(buffer, nb, len));
  return (len);
}
