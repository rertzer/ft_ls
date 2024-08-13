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

unsigned int	format_links(char *buffer, t_data *data)
{
	return (ft_itoa_dec(data->links, buffer));
}

unsigned int format_size(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (!(data->file.type == CHR || data->file.type == BLK))
	{
		size = ft_itoa_dec(data->total_size, buffer);
	}

	return (size);
}

unsigned int format_minor(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->file.type == CHR || data->file.type == BLK)
	{
		size = ft_itoa_dec(minor(data->rdev), buffer);
	}

	return (size);
}

unsigned int format_major(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->file.type == CHR || data->file.type == BLK)
	{
		size = ft_itoa_dec(major(data->rdev), buffer);
	}

	return (size);
}

unsigned int format_time(char *buffer, t_data *data)
{
	unsigned int	size;
	
	char	*time_string = get_time_string(&data->time.tv_sec);

	if (time_string == NULL)
	{
		size = 0;
	}
	else if (recent(data->time.tv_sec, time_string))
	{
		size = format_recent_time(buffer, time_string);
	}
	else
	{
		size = format_late_time(buffer, time_string);
	}

	return (size);
}

unsigned int format_recent_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[0], &time_string[4], 12);
	buffer[12] = '\0';
	return (12);
}

unsigned int format_late_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[0], &time_string[4], 7);
	ft_bufferncpy(&buffer[8], &time_string[20], 4);
	buffer[7]= ' ';
	buffer[12] = '\0';
	return (12);
}

unsigned int	format_name(char **buffer, t_data *data)
{
	*buffer = data->file.name;
	return (ft_strlen(*buffer));
}

void	format_symlink(char **buffer, t_data *data)
{
	*buffer = data->target.name;
}
