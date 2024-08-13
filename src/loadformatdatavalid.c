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

	format_data->align_user_left = true;
	format_data->align_group_left = true;

	format_mode(format_data->mode, &format_sizes->mode, data);
	format_links(format_data->links, &format_sizes->links, data);

	ret = format_user(strat, format_data, &format_sizes->user, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}

	ret = format_group(strat, format_data, &format_sizes->group, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}

	format_size(format_data->size,&format_sizes->size, data);
	format_minor(format_data->minor, &format_sizes->minor, data);
	format_major(format_data->major, &format_sizes->major, data);
	ret = format_time(format_data->date, &format_sizes->date, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	format_name(&format_data->name, &format_sizes->name, data);
	format_symlink(&format_data->target, data);

	strat->color(&format_data->color, &data->file);
	if (data->target.name != NULL)
	{
		strat->color(&format_data->target_color, &data->target);
	}

	return (ret);
}

