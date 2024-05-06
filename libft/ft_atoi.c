/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:16:43 by rertzer           #+#    #+#             */
/*   Updated: 2024/02/10 10:28:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_space(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] && ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' '))
		++i;
	return (&nptr[i]);
}

static int	get_sign(const char *nptr)
{
	int	sign;

	sign = 1;
	if (nptr[0] == '-')
		sign = -1;
	return (sign);
}

static const char	*skip_sign(const char *nptr)
{
	if (nptr[0] == '+' || nptr[0] == '-')
		nptr = &nptr[1];
	return (nptr);
}

static	int	get_int_value(const char *nptr)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			total = total * 10 + nptr[i] - ASCII_CODE_ZERO;
		else
			break ;
		++i;
	}
	return (total);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		total;

	nptr = skip_space(nptr);
	sign = get_sign(nptr);
	nptr = skip_sign(nptr);
	total = get_int_value(nptr);
	return (sign * total);
}
