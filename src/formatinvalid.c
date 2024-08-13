/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatinvalid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:30:17 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 11:30:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int			format_mode_invalid(char *buffer, t_data *data);
static inline unsigned int	format_links_invalid(char *buffer);
static unsigned int			format_user_or_group_invalid(char **buffer);
static inline unsigned int	format_size_invalid(char *buffer);
static inline unsigned int	format_date_invalid(char *buffer);

int	load_format_data_invalid(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
	unsigned int	size = 0;

	format_data->align_user_left = true;
	format_data->align_group_left = true;
	
	size = format_mode_invalid(format_data->mode, data);
	set_max_size(&format_sizes->mode, size);
	
	size = format_links_invalid(format_data->links);
	set_max_size(&format_sizes->links, size);
	
	size = format_user_or_group_invalid(&format_data->user);
	set_max_size(&format_sizes->user, size);

	size = format_user_or_group_invalid(&format_data->group);
	set_max_size(&format_sizes->group, size);

	size = format_size_invalid(format_data->size);
	set_max_size(&format_sizes->size, size);

	size = format_date_invalid(format_data->date);	
	set_max_size(&format_sizes->date, size);

	size = format_name(&format_data->name, data);
	set_max_size(&format_sizes->name, size);

	format_data->target = NULL;
	strat->color(&format_data->color, &data->file);

	return (OK);
}

static unsigned int	format_mode_invalid(char *buffer, t_data *data)
{
	unsigned int	size = 10;

	format_mode_type(buffer, data);
	buffer[size] = '\0';
	for (unsigned int i = 1; i < size ; ++i)
	{
		buffer[i] = '?';
	}
	return (size);
}

static inline unsigned int	format_links_invalid(char *buffer)
{
	unsigned int	size = 1;

	buffer[0] = '?';
	buffer[1] = '\0';

	return (size);
}

static unsigned int	format_user_or_group_invalid(char **buffer)
{
	static char		question_mark[2] = "?\0";
	unsigned int	size = 1;

	*buffer = question_mark;

	return (size);
}

static inline unsigned int	format_size_invalid(char *buffer)
{
	unsigned int	size = 1;

	buffer[0] = '?';
	buffer[1] = '\0';

	return (size);
}

static inline unsigned int	format_date_invalid(char *buffer)
{
	unsigned int	size = 12;

	for(unsigned int i = 0; i < (size - 1); ++i)
	{
		buffer[i] = ' ';
	}

	buffer[size - 1] = '?';
	buffer[size] = '\0';

	return (size);
}
