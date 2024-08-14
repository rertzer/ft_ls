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

static void	format_mode_invalid(char *buffer, unsigned int *format_size, t_data *data);
static void	format_links_invalid(char *buffer, unsigned int *format_size);
static void	format_user_or_group_invalid(char **buffer, unsigned int *format_size);
static void	format_size_invalid(char *buffer, unsigned int *format_size);
static void	format_date_invalid(char *buffer, unsigned int *format_size);

int	load_format_data_invalid(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
	format_data->align_user_left = true;
	format_data->align_group_left = true;
	
	format_mode_invalid(format_data->mode, &format_sizes->mode, data);
	format_links_invalid(format_data->links, &format_sizes->links);
	format_user_or_group_invalid(&format_data->user, &format_sizes->user);
	format_user_or_group_invalid(&format_data->group, &format_sizes->group);
	format_size_invalid(format_data->size, &format_sizes->size);
	format_date_invalid(format_data->date, &format_sizes->date);	
	format_name(&format_data->name, &format_sizes->name, data);

	format_data->target = NULL;
	strat->color(&format_data->color, &data->file);

	return (OK);
}

static void	format_mode_invalid(char *buffer, unsigned int *format_size, t_data *data)
{
	unsigned int	size = 10;

	format_mode_type(buffer, data);
	buffer[size] = '\0';
	for (unsigned int i = 1; i < size ; ++i)
	{
		buffer[i] = '?';
	}
	set_max_size(format_size, size);
}

static void	format_links_invalid(char *buffer, unsigned int *format_size)
{
	unsigned int	size = 1;

	buffer[0] = '?';
	buffer[1] = '\0';

	set_max_size(format_size, size);
}

static void	format_user_or_group_invalid(char **buffer, unsigned int *format_size)
{
	static char		question_mark[2] = "?\0";
	unsigned int	size = 1;

	*buffer = question_mark;

	set_max_size(format_size, size);
}

static void	format_size_invalid(char *buffer, unsigned int *format_size)
{
	unsigned int	size = 1;

	buffer[0] = '?';
	buffer[1] = '\0';

	set_max_size(format_size, size);
}

static void	format_date_invalid(char *buffer, unsigned int *format_size)
{
	unsigned int	size = 12;

	for(unsigned int i = 0; i < (size - 1); ++i)
	{
		buffer[i] = ' ';
	}

	buffer[size - 1] = '?';
	buffer[size] = '\0';

	set_max_size(format_size, size);
}
