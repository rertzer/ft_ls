/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadformatdatavalid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:04:27 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 13:04:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	load_format_data_valid(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
	int				ret = OK;
	unsigned int	size = 0;

	format_data->align_user_left = true;
	format_data->align_group_left = true;
	size = format_mode(format_data->mode, data);
	set_max_size(&format_sizes->mode, size);
	
	size = format_links(format_data->links, data);
	set_max_size(&format_sizes->links, size);
	
	ret = format_user(strat, format_data, &size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	set_max_size(&format_sizes->user, size);

	ret = format_group(strat, format_data, &size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	set_max_size(&format_sizes->group, size);

	size = format_size(format_data->size, data);
	set_max_size(&format_sizes->size, size);
	
	size = format_minor(format_data->minor, data);
	set_max_size(&format_sizes->minor, size);
	
	size = format_major(format_data->major, data);
	set_max_size(&format_sizes->major, size);

	size = format_time(format_data->date, data);
	if (size == 0)
	{
		return (INTERNAL_KO);
	}
	set_max_size(&format_sizes->date, size);

	size = format_name(&format_data->name, data);
	set_max_size(&format_sizes->name, size);

	format_symlink(&format_data->target, data);

	strat->color(&format_data->color, &data->file);
	if (data->target.name != NULL)
	{
		strat->color(&format_data->target_color, &data->target);
	}
	return (ret);
}

