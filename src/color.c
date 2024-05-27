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

int no_color(e_color_type *color_type, t_file *file)
{
	(void)file;
	*color_type = COLOR_TYPE_DEFT;

	return (OK);
}

const char	*get_color_str(e_color_type color)
{
	static const char	*colors[] = {
		COLOR_DEFT,
		COLOR_DIRE,
		COLOR_LINK,
		COLOR_EXEC,
		COLOR_ARCH,
		COLOR_FIFO,
		COLOR_BKLN,
		COLOR_SOCK,
		COLOR_IMAG,
		COLOR_AUDI,
		COLOR_BLCK,
		COLOR_CHAR,
		COLOR_SUID,
		COLOR_SGID,
		COLOR_CAPA,
		COLOR_SKDR,
		COLOR_OWDR,
		COLOR_SOWD
	};

	if (color < 0 || color >= COLOR_TYPE_NUMBER)
	{
		color = COLOR_TYPE_DEFT;
	}

	return (colors[color]);
}
