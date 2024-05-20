/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:46:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/14 10:46:54 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int					load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data);
static inline void			load_block_size(t_directory *dir, t_data *data);
static unsigned int			format_mode(char *buffer, t_data *data);
static inline void			format_mode_type(char *buffer, t_data *data);
static inline void			format_mode_user(char *buffer, t_data *data);
static inline void			format_mode_group(char *buffer, t_data *data);
static inline void			format_mode_other(char *buffer, t_data *data);
static inline unsigned int	format_mode_xattr(char *buffer, t_data *data, unsigned int size);
static unsigned int			format_links(char *buffer, t_data *data);
static unsigned int			format_user(t_strategies *strat, char **buffer, t_data *data);
static unsigned int			format_group(t_strategies *strat, char **buffer, t_data *data);
static unsigned int			format_size(char *buffer, t_data *data);
static unsigned int			format_minor(char *buffer, t_data *data);
static unsigned int			format_major(char *buffer, t_data *data);
static unsigned int			format_time(char *buffer, t_data *data);
static unsigned int			format_recent_time(char *buffer, char *time_string);
static unsigned int			format_late_time(char *buffer, char *time_string);
static void					format_symlink(char **buffer, t_data *data);
static void					set_max_size(unsigned int *max, unsigned int size);

int  load_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data * all_format_data)
{
	int		ret = OK;
	int		i = 0;
	t_list	*entry = dir->content;

	while (entry != NULL)
	{
		t_data	*data = (t_data*)entry->content;

		load_block_size(dir, data);
		ret = load_format_data(strat, data, format_sizes, &all_format_data[i]);
		if (ret != OK)
		{
			break;
		}
		entry = entry->next;
		++i;
	}
	set_max_size(&format_sizes->size, format_sizes->minor + format_sizes->major + 2);

	return (ret);
}

static inline void	load_block_size(t_directory *dir, t_data *data)
{
	dir->total_block_size +=  data->block_nb / 2;
}

static int	load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
	size_t  size = 0;

	size = format_mode(format_data->mode, data);
	set_max_size(&format_sizes->mode, size);
	
	size = format_links(format_data->links, data);
	set_max_size(&format_sizes->links, size);
	
	size = format_user(strat, &format_data->user, data);
	set_max_size(&format_sizes->user, size);
	
	size = format_group(strat, &format_data->group, data);
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
		return (MAJOR_KO);
	}
	set_max_size(&format_sizes->date, size);

	size = format_name(&format_data->name, data);
	set_max_size(&format_sizes->name, size);

	format_symlink(&format_data->target, data);

	strat->color(&format_data->color, data);

	return (OK);
}

static unsigned int	format_mode(char *buffer, t_data *data)
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

static inline void	format_mode_type(char *buffer, t_data *data)
{
	char	types[] = {'-', 'd', 'c', 'b', 'p', 'l', 's'};

	buffer[0] = types[data->mode.type];
}

static inline void	format_mode_user(char *buffer, t_data *data)
{
	buffer[1] = (data->mode.mode & S_IRUSR) ? 'r' : '-';
	buffer[2] = (data->mode.mode & S_IWUSR) ? 'w' : '-';

	if (data->mode.mode & S_ISUID)
	{
		buffer[3] = (data->mode.mode & S_IXUSR) ? 's' : 'S';
	}
	else
	{
		buffer[3] = (data->mode.mode & S_IXUSR) ? 'x' : '-';
	}
}

static inline void	format_mode_group(char *buffer, t_data *data)
{
	buffer[4] = (data->mode.mode & S_IRGRP) ? 'r' : '-';
	buffer[5] = (data->mode.mode & S_IWGRP) ? 'w' : '-';
	
	if (data->mode.mode & S_ISGID)
	{
		buffer[6] = (data->mode.mode & S_IXGRP) ? 's' : 'S';
	}
	else
	{
		buffer[6] = (data->mode.mode & S_IXGRP) ? 'x' : '-';
	}
}

static inline void	format_mode_other(char *buffer, t_data *data)
{
	buffer[7] = (data->mode.mode & S_IROTH) ? 'r' : '-';
	buffer[8] = (data->mode.mode & S_IWOTH) ? 'w' : '-';
	
	if (data->mode.mode & S_ISVTX)
	{
		buffer[9] = (data->mode.mode & S_IXOTH) ? 't' : 'T';
	}
	else
	{
		buffer[9] = (data->mode.mode & S_IXOTH) ? 'x' : '-';
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

static unsigned int	format_links(char *buffer, t_data *data)
{
	return (ft_itoa_dec(data->links, buffer));
}

static unsigned int format_user(t_strategies *strat, char **buffer, t_data *data)
{
	*buffer = get_user_name(strat, data->uid);
	return (ft_strlen(*buffer));
}

static unsigned int format_group(t_strategies *strat, char **buffer, t_data *data)
{
	*buffer = get_group_name(strat, data->gid);
	return (ft_strlen(*buffer));
}

static unsigned int format_size(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (!(data->mode.type == CHR || data->mode.type == BLK))
	{
		size = ft_itoa_dec(data->total_size, buffer);
	}

	return (size);
}

static unsigned int format_minor(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->mode.type == CHR || data->mode.type == BLK)
	{
		size = ft_itoa_dec(minor(data->rdev), buffer);
	}

	return (size);
}

static unsigned int format_major(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->mode.type == CHR || data->mode.type == BLK)
	{
		size = ft_itoa_dec(major(data->rdev), buffer);
	}

	return (size);
}

static unsigned int format_time(char *buffer, t_data *data)
{
	unsigned int	size = 0;
	
	char	*time_string = get_time_string(&data->time);
	if (time_string == NULL)
	{
		return 0;
	}

	if (recent(time_string))
	{
		size = format_recent_time(buffer, time_string);
	}
	else
	{
		size = format_late_time(buffer, time_string);
	}

	free(time_string);
	
	return (size);
}

static unsigned int format_recent_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[0], &time_string[4], 12);
	buffer[12] = '\0';
	return (12);
}

static unsigned int format_late_time(char *buffer, char *time_string)
{
	ft_bufferncpy(&buffer[0], &time_string[4], 7);
	ft_bufferncpy(&buffer[8], &time_string[20], 4);
	buffer[7]= ' ';
	buffer[12] = '\0';
	return (12);
}

unsigned int	format_name(char **buffer, t_data *data)
{
	*buffer = data->name;
	return (ft_strlen(*buffer));
}

static void	format_symlink(char **buffer, t_data *data)
{
	*buffer = data->target;
}

static void set_max_size(unsigned int *max, unsigned int size)
{
	if (size > *max)
	{
		*max = size;
	}
}

