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
static int					format_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data);
static unsigned int 		format_user_id(char **buffer, t_data *data);
static int					format_group(t_strategies *strat, char **buffer, unsigned int *len, t_data *data);
static unsigned int 		format_group_id(char **buffer, t_data *data);
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
		if (ret == INTERNAL_KO)
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
	int				ret = OK;
	unsigned int	size = 0;

	format_data->align_user_left = true;
	format_data->align_group_left = true;
	size = format_mode(format_data->mode, data);
	set_max_size(&format_sizes->mode, size);
	
	size = format_links(format_data->links, data);
	set_max_size(&format_sizes->links, size);
	
	ret = format_user(strat, &format_data->user, &size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	if (size == 0)
	{
		size = format_user_id(&format_data->user, data);
		if (size == 0)
		{
			return (INTERNAL_KO);
		}
		format_data->align_user_left = false;
	}
	set_max_size(&format_sizes->user, size);
	
	ret = format_group(strat, &format_data->group, &size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	if (size == 0)
	{
		size = format_group_id(&format_data->group, data);
		if (size == 0)
		{
			return (INTERNAL_KO);
		}
		format_data->align_group_left = false;
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

static unsigned int	format_links(char *buffer, t_data *data)
{
	return (ft_itoa_dec(data->links, buffer));
}

static int format_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data)
{
	int	ret = OK;

	ret = get_user_name(strat, buffer, data->uid);
	if (ret == OK && *buffer != NULL)
	{
		*len = ft_strlen(*buffer);
	}
	else
	{
		*len = 0;
	}
	return (ret);
}

static unsigned int format_user_id(char **buffer, t_data *data)
{
	unsigned int	len = 0;
	*buffer = ft_itoa(data->uid);
	if (buffer != NULL)
	{
		len = ft_strlen(*buffer);
	}
	return (len);
}

static int format_group(t_strategies *strat, char **buffer, unsigned int *len, t_data *data)
{
	int	ret = OK;
	ret = get_group_name(strat, buffer, data->gid);
	if (ret == OK && *buffer != NULL)
	{
		*len = ft_strlen(*buffer);
	}
	else
	{
		*len = 0;
	}
	return (ret);
}

static unsigned int format_group_id(char **buffer, t_data *data)
{
	unsigned int	len = 0;
	*buffer = ft_itoa(data->gid);
	if (buffer != NULL)
	{
		len = ft_strlen(*buffer);
	}
	return (len);
}

static unsigned int format_size(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (!(data->file.type == CHR || data->file.type == BLK))
	{
		size = ft_itoa_dec(data->total_size, buffer);
	}

	return (size);
}

static unsigned int format_minor(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->file.type == CHR || data->file.type == BLK)
	{
		size = ft_itoa_dec(minor(data->rdev), buffer);
	}

	return (size);
}

static unsigned int format_major(char *buffer, t_data *data)
{
	unsigned int	size = 0;

	if (data->file.type == CHR || data->file.type == BLK)
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

	if (recent(data->time, time_string))
	{
		size = format_recent_time(buffer, time_string);
	}
	else
	{
		size = format_late_time(buffer, time_string);
	}

	//free(time_string);
	
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
	*buffer = data->file.name;
	return (ft_strlen(*buffer));
}

static void	format_symlink(char **buffer, t_data *data)
{
	*buffer = data->target.name;
}

static void set_max_size(unsigned int *max, unsigned int size)
{
	if (size > *max)
	{
		*max = size;
	}
}

