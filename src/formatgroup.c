/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatgroup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:45:01 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 13:45:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int format_group_group(t_strategies* strat, char** buffer, unsigned int* len, t_data* data);
static unsigned int format_group_id(t_format_data* format_data, t_data* data);

int format_group(t_strategies*	strat,
				 t_format_data* format_data,
				 unsigned int*	format_size,
				 t_data*		data) {
	unsigned int size;
	int			 ret = format_group_group(strat, &format_data->group, &size, data);

	if (ret != INTERNAL_KO) {
		if (size == 0) {
			size = format_group_id(format_data, data);
			if (size == 0) {
				ret = INTERNAL_KO;
			}
		}
		set_max_size(format_size, size);
	}

	return (ret);
}

static int format_group_group(t_strategies* strat, char** buffer, unsigned int* len, t_data* data) {
	int ret = get_group_name(strat, buffer, len, data->gid);

	return (ret);
}

static unsigned int format_group_id(t_format_data* format_data, t_data* data) {
	unsigned int len = 0;

	format_data->group = ft_itoa(data->gid);
	if (format_data->group != NULL) {
		len = ft_strlen(format_data->group);
		format_data->align_group_left = false;
	}

	return (len);
}
