/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:15:31 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/02 10:50:52 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_get_sign(int nb);
static unsigned int ft_get_len(unsigned int unb, int sign);
static char*		add_digits(char* str, unsigned int unb, unsigned int len);
static char*		add_sign(char* str, int sign);

char* ft_itoa(int nb) {
	unsigned int unb;
	unsigned int len;
	int			 sign;
	char*		 str;

	sign = ft_get_sign(nb);
	unb = nb * sign;
	len = ft_get_len(unb, sign);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	str = add_digits(str, unb, len);
	str = add_sign(str, sign);
	return (str);
}

static int ft_get_sign(int nb) {
	int sign;

	if (nb < 0) {
		sign = -1;
	} else {
		sign = 1;
	}
	return (sign);
}

static unsigned int ft_get_len(unsigned int unb, int sign) {
	unsigned int len;

	len = 1;
	unb /= 10;
	while (unb) {
		++len;
		unb /= 10;
	}
	if (sign < 0)
		++len;
	return (len);
}

static char* add_digits(char* str, unsigned int unb, unsigned int len) {
	if (unb == 0) {
		str[0] = '0';
	}
	while (unb) {
		len--;
		str[len] = (unb % 10) + '0';
		unb /= 10;
	}
	return (str);
}

static char* add_sign(char* str, int sign) {
	if (sign < 0)
		str[0] = '-';
	return (str);
}
