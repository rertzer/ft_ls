/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:19:05 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/14 09:20:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


int	worst(int ret1, int ret2)
{
	return (ret1 > ret2 ? ret1 : ret2);
}

int	major_status(int ret)
{
	if (ret == MINOR_KO)
	{
		ret = MAJOR_KO;
	}

	return (ret);
}
