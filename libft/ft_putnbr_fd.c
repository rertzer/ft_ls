/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:42:27 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/09 09:53:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	print_unbr_fd(unsigned int n, int fd);
static void	print_digit_fd(unsigned int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	unbr;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		unbr = n * -1;
	}
	else
		unbr = n;
	print_unbr_fd(unbr, fd);
}

static void	print_unbr_fd(unsigned int unbr, int fd)
{
	if (unbr > 9)
	{
		print_unbr_fd(unbr / 10, fd);
		print_unbr_fd(unbr % 10, fd);
	}
	else
		print_digit_fd(unbr, fd);
}

static void	print_digit_fd(unsigned int n, int fd)
{
	char	c;

	c = '0' + (char)n;
	write(fd, &c, 1);
}
