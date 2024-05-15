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
