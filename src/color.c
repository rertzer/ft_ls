/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:31 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/18 14:26:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int no_color(e_color_type *color_type, t_data *data)
{
	*color_type = COLOR_TYPE_DEFT;
	(void)data;

	return (OK);
}
