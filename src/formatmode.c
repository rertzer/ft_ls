/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:14:05 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 11:14:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void			format_mode_user(char *buffer, t_data *data);
static inline void			format_mode_group(char *buffer, t_data *data);
static inline void			format_mode_other(char *buffer, t_data *data);
static inline unsigned int	format_mode_xattr(char *buffer, t_data *data, unsigned int size);

unsigned int	format_mode(char *buffer, t_data *data)
{
	unsigned int	size = 10;

	format_mode_type(buffer, data);
	format_mode_user(buffer, data);
	format_mode_group(buffer, data);
	format_mode_other(buffer, data);	
	size = format_mode_xattr(buffer, data, size);
	
	buffer[size] = '\0';

	return (size);
}

void	format_mode_type(char *buffer, t_data *data)
{
	char	types[] = {'-', 'd', 'c', 'b', 'p', 'l', 's'};

	buffer[0] = types[data->file.type];
}

static inline void	format_mode_user(char *buffer, t_data *data)
{
	buffer[1] = (data->file.mode & S_IRUSR) ? 'r' : '-';
	buffer[2] = (data->file.mode & S_IWUSR) ? 'w' : '-';

	if (data->file.mode & S_ISUID)
	{
		buffer[3] = (data->file.mode & S_IXUSR) ? 's' : 'S';
	}
	else
	{
		buffer[3] = (data->file.mode & S_IXUSR) ? 'x' : '-';
	}
}

static inline void	format_mode_group(char *buffer, t_data *data)
{
	buffer[4] = (data->file.mode & S_IRGRP) ? 'r' : '-';
	buffer[5] = (data->file.mode & S_IWGRP) ? 'w' : '-';
	
	if (data->file.mode & S_ISGID)
	{
		buffer[6] = (data->file.mode & S_IXGRP) ? 's' : 'S';
	}
	else
	{
		buffer[6] = (data->file.mode & S_IXGRP) ? 'x' : '-';
	}
}

static inline void	format_mode_other(char *buffer, t_data *data)
{
	buffer[7] = (data->file.mode & S_IROTH) ? 'r' : '-';
	buffer[8] = (data->file.mode & S_IWOTH) ? 'w' : '-';
	
	if (data->file.mode & S_ISVTX)
	{
		buffer[9] = (data->file.mode & S_IXOTH) ? 't' : 'T';
	}
	else
	{
		buffer[9] = (data->file.mode & S_IXOTH) ? 'x' : '-';
	}
}

static inline unsigned int	format_mode_xattr(char *buffer, t_data *data, unsigned int size)
{
	if (data->xattr == true)
	{
		++size;
		buffer[10] = '+';
	}
	
	return (size);
}

