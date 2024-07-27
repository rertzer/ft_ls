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
static int	add_symlink_standard(t_data *data);
static int	add_symlink_nullsize(t_data *data);
static int	set_symlink_type(t_data *data);
static int	set_invalid_target_name(t_data *data, int buffer_size);
static int	symlink_error(t_data *data);

int	add_symlink(t_data *data)
{
	if (data->total_size == 0)
	{
		return (add_symlink_nullsize(data));
	}
	else
	{
		return (add_symlink_standard(data));
	}
}

static int	add_symlink_standard(t_data *data)
{
	int	ret = OK;
	
	data->target.name = ft_malloc(sizeof(char) * (data->total_size + 1));
	if (data->target.name == NULL)
	{
		return (INTERNAL_KO);
	}

	errno = 0;
	ssize_t	size = readlink(data->path, data->target.name, data->total_size);
	if (size < 0)
	{
		return (symlink_error(data));
	}
	data->target.name[size] = '\0';
	ret = set_symlink_type(data);
	if (size != (ssize_t)data->total_size)
	{
		printf("bad size %zu %zd\n", data->total_size, size);
		printf("%s type is %d\n", data->target.name, data->target.type);
		ret = set_invalid_target_name(data, size);
	}

	return (ret);
}

static int add_symlink_nullsize(t_data *data)
{
	int	ret = OK;
	int	buffer_size = 128;
	
	data->target.name = ft_malloc(sizeof(char) * (buffer_size + 1));
	if (data->target.name == NULL)
	{
		return (INTERNAL_KO);
	}

	errno = 0;
	ssize_t	size = readlink(data->path, data->target.name, buffer_size);
	if (size < 0 || size > 128)
	{
		printf ("size is %zd\n", size);
		return (symlink_error(data));
	}

	data->target.name[size] = '\0';
	if (data->target.name[0] != '/')
	{
		ret = set_invalid_target_name(data, size);
	}
	ret = set_symlink_type(data);

	return (ret);
}

static int	set_invalid_target_name(t_data *data, int buffer_size)
{
	char *buffer = data->target.name;
	data->target.name = ft_malloc(sizeof(char) * (buffer_size + 3));
	if (data->target.name == NULL)
	{
		free(buffer);
		return (INTERNAL_KO);
	}

	ft_strcpy(&data->target.name[1], buffer);
	free(buffer);
	
	data->target.name[0] = '\'';
	data->target.name[buffer_size + 1] = '\'';
	data->target.name[buffer_size + 2] = '\0';

	return (OK);
}

static int	set_symlink_type(t_data *data)
{
	int			ret = OK;
	struct stat	stat_buffer;
    
	errno = 0;
	if (stat(data->path, &stat_buffer) != 0)
	{
		if (errno == ENOENT)
		{
			data->target.type = ERROR_TYPE;
			data->file.broken = true;
		}
		else
		{
			ret = MINOR_KO;
			data->target.type = ERROR_TYPE;
			ft_putstr_fd("ft_ls: stat: ", 2);
			perror(data->path);
		}
	}
	else 
	{
    	data->target.type = get_type(stat_buffer.st_mode);
		data->target.mode = stat_buffer.st_mode;
		printf("path %s has type %d\n", data->path, data->target.type);
		if (data->target.type == ERROR_TYPE)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(data->file.name, 2);
			ft_putstr_fd(": invalid file type\n", 2);
			ret = MINOR_KO;
		}
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
