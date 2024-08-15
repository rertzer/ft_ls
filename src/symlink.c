/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symlink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:59:10 by rertzer           #+#    #+#             */
/*   Updated: 2024/07/27 09:59:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

static int	get_symlink_buffer_size(t_data *data);
static int	set_target_name(t_data *data, ssize_t *size, int buffer_size);
static int	handle_symlink_type(t_data *data, ssize_t size, int buffer_size);
static int	set_symlink_type(t_data *data);
static char	*get_pathname(t_data *data);
static int	set_target_type(t_data *data, struct stat *stat_buffer);
static int	symlink_error(t_data *data);
static int	handle_stat_error(t_data *data);
static int	stat_error(t_data *data);
static int	target_type_error(t_data *data);

int	add_symlink(t_data *data)
{
	int		ret = OK;
	int		buffer_size = get_symlink_buffer_size(data);
	ssize_t	size = 0;

	data->target.name = ft_malloc(sizeof(char) * (buffer_size + 1));
	if (data->target.name == NULL)
	{
		return (INTERNAL_KO);
	}

	ret = set_target_name(data, &size, buffer_size);

	if (ret == OK)
	{
		ret = handle_symlink_type(data, size, buffer_size);
	}

	return (ret);
}

static int	get_symlink_buffer_size(t_data *data)
{
	int	buffer_size;

	if ((data->total_size == 0 || data->total_size == 64) && ((! ft_strncmp("/proc/", data->path, 6)) || (! ft_strncmp("/sys/", data->path, 5))))
	{
		buffer_size = 4096;
	}
	else
	{
		buffer_size = data->total_size;
	}

	return (buffer_size);
}

static int	set_target_name(t_data *data, ssize_t *size, int buffer_size)
{
	errno = 0;
	*size = readlink(data->path, data->target.name, buffer_size);
	if (*size < 0)
	{
		return (symlink_error(data));
	}
	data->target.name[*size] = '\0';

	return (OK);
}

static int	handle_symlink_type(t_data *data, ssize_t size, int buffer_size)
{
	int	ret = OK;

	if (size != (ssize_t)buffer_size && (data->target.name[0] != '/' || data->target.name[size - 1] == ')'))
	{
		data->target.type = ERROR_TYPE;
		data->file.broken = true;
	}
	else
	{
		ret = set_symlink_type(data);
	}

	return (ret);
}

static int	set_symlink_type(t_data *data)
{
	int			ret = OK;
	struct stat	stat_buffer;
	char		*path_name = get_pathname(data); 

	errno = 0;
	if (stat(path_name, &stat_buffer) != 0)
	{
		ret = handle_stat_error(data);
	}
	else 
	{
		ret = set_target_type(data, &stat_buffer);
   	}

	return (ret);
}

static char	*get_pathname(t_data *data)
{
	char	*path_name = data->path;

    if (data->target.name[0] == '/')
	{
		path_name = data->target.name;
	}

	return (path_name);
}

static int	set_target_type(t_data *data, struct stat *stat_buffer)
{
	int	ret = OK;

 	data->target.type = get_type(stat_buffer->st_mode);
	data->target.mode = stat_buffer->st_mode;
	if (data->target.type == ERROR_TYPE)
	{
		ret = target_type_error(data);	
	}

	return (ret);
}

static int	symlink_error(t_data *data)
{
	print_perror_msg("cannot read symbolic link '", data->path); 
	free(data->target.name);
	data->target.name = NULL;
	data->target.type = ERROR_TYPE;
	data->file.broken = true;
	
	return (MINOR_KO);
}

static int	handle_stat_error(t_data *data)
{
	int	ret = OK;

	if (errno == ENOENT)
	{
		data->target.type = ERROR_TYPE;
		data->file.broken = true;
	}
	else
	{
		ret = stat_error(data);
	}
	
	return (ret);
}

static int	stat_error(t_data *data)
{
		data->target.type = ERROR_TYPE;
		data->file.broken = true;
		if (errno != ELOOP)
		{
			ft_putstr_fd("ft_ls: stat: ", 2);
			perror(data->path);
		}

		return (MINOR_KO);
}

static int	target_type_error(t_data *data)
{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(data->file.name, 2);
		ft_putstr_fd(": invalid file type\n", 2);
		
		return (MINOR_KO);
}
