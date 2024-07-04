/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:34:00 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 14:34:02 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void  print_char_error(char *message, char param)
{
	char	param_string[] = "'X'\n";
	
	param_string[1] = param;

	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(param_string, 2);
}

void	print_error_msg(char *message, char *param)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("'\n", 2);
}

int		print_perror_msg(char *message, char *param)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(param, 2);
	perror("'");
	return (MINOR_KO);
}

int	xattr_error(t_data *data)
{
	int	ret = OK;

	if (errno == ENOENT || errno == ELOOP)
	{
		data->xattr = false;
	}
	else
	{
		ft_putstr_fd("ft_ls: listxattr: ", 2);
		perror(data->path);
	}
	return (ret);
}
