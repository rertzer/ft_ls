/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:18:23 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/18 09:18:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_inset(const char *str, const char **set)
{
	bool	inset = false;

	for (int i = 0 ; set[i] != NULL; ++i)
	{
		if (ft_strcmp(str, set[i]) == 0)
		{
			inset = true;
			break;
		}
	}
	return (inset);
}
