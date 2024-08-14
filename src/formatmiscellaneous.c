/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatmiscellaneous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:22:31 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 13:22:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int format_recent_time(char *buffer, char *time_string);
static unsigned int format_late_time(char *buffer, char *time_string);
bool	is_device_file(t_data *data);

void	format_links(char *buffer, unsigned int *format_size, t_data *data)
{
	unsigned int size = ft_itoa_dec(data->links, buffer);
	set_max_size(format_size, size);
}

void format_size(char *buffer, unsigned int *format_size, t_data *data)
{
	unsigned int	size = 0;

	if (is_device_file(data) == false)
	{
		size = ft_itoa_dec(data->total_size, buffer);
	}

	set_max_size(format_size, size);
}

void format_minor(char *buffer, unsigned int *format_size, t_data *data)
{
	unsigned int	size = 0;

	if (is_device_file(data) == true)
	{
		size = ft_itoa_dec(minor(data->rdev), buffer);
	}

	set_max_size(format_size, size);
}

void format_major(char *buffer, unsigned int *format_size, t_data *data)
{
	unsigned int	size = 0;

	if (is_device_file(data) == true)
	{
		size = ft_itoa_dec(major(data->rdev), buffer);
	}

	set_max_size(format_size, size);
}

int	format_time(char *buffer, unsigned int *format_size, t_data *data)
{
	int				ret = OK;
	unsigned int	size;
	
	char	*time_string = get_time_string(&data->time.tv_sec);

	if (time_string == NULL)
	{
		size = 0;
		ret = INTERNAL_KO;
	}
	else if (recent(data->time.tv_sec, time_string))
	{
		size = format_recent_time(buffer, time_string);
	}
	else
	{
		size = format_late_time(buffer, time_string);
	}

	set_max_size(format_size, size);

	return (ret);
}

/*
	ctime format	: Wed Jun 30 21:49:08 1993
	ls recent format: Jun 30 21:49
	ls late format	: Jun 30  1993

*/
static unsigned int format_recent_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[LS_MONTH_OFFSET], &time_string[CTIME_MONTH_OFFSET], 12);
	buffer[12] = '\0';
	return (12);
}

static unsigned int format_late_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[LS_MONTH_OFFSET], &time_string[CTIME_MONTH_OFFSET], 7);
	ft_bufferncpy(&buffer[LS_YEAR_OFFSET], &time_string[CTIME_YEAR_OFFSET], 4);
	buffer[7]= ' ';
	buffer[12] = '\0';
	return (12);
}

void	format_name(char **buffer, unsigned int *format_size, t_data *data)
{
	*buffer = data->file.name;
	set_max_size(format_size, ft_strlen(*buffer));
}

void	format_symlink(char **buffer, t_data *data)
{
	*buffer = data->target.name;
}


