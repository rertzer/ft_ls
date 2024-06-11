/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:52:09 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/14 10:52:24 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int	print_format_mode(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_links(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_size_field(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_size(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_device(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_date(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_long_ending(char *dest, t_format_data *format_data, unsigned int offset);
static void			print_format_symlink(t_format_data *format_data);
static	void		space_feed(void *v, int n);
//static unsigned int	get_end_pos(t_format_sizes *format_sizes);

int	print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	char			buffer[1024];
	unsigned int	offset = 1024;

	if (strat->printformat == print_format_data_short)
	{
		offset = 280;
	}

	for (unsigned int i = 0; i < dir->entry_nb; ++i)
	{
		space_feed(buffer, offset);
		offset = strat->printformat(strat, &all_format_data[i], format_sizes, buffer);
	}

	return (OK);
}

int	print_format_data_short(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes, char *buffer)
{
	(void)strat;
	(void)format_sizes;

	unsigned int	offset = 0;

	offset += print_format_color(buffer, format_data, offset);
	offset += print_format_name(buffer, format_data, offset);
	offset += print_format_color_reset(buffer, offset);
	offset += print_format_short_ending(buffer, offset);

	write(1, buffer, offset);
	if (format_data->align_user_left == false)
	{
		free(format_data->user);
		format_data->name = NULL;
	}
	if (format_data->align_group_left == false)
	{
		free(format_data->group);
		format_data->group = NULL;
	}

	return (offset);
}

int	print_format_data_long(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes, char *buffer)
{
	unsigned int	offset = 0;

	offset += print_format_mode(buffer, format_data, format_sizes, offset);
	offset += print_format_links(buffer, format_data, format_sizes, offset);
	offset += strat->printuser(buffer, format_data, format_sizes, offset);
	offset += strat->printgroup(buffer, format_data, format_sizes, offset);
	offset += print_format_size_field(buffer, format_data, format_sizes, offset);
	offset += print_format_date(buffer, format_data, format_sizes, offset);
	offset += print_format_color(buffer, format_data, offset);
	offset += print_format_name(buffer, format_data, offset);
	offset += print_format_color_reset(buffer, offset);
	offset += print_format_long_ending(buffer, format_data, offset);

	write(1, buffer, offset);
	print_format_symlink(format_data);

	return (offset);
}

static unsigned int	print_format_mode(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->mode);
	return (format_sizes->mode + 1);
}

static unsigned int	print_format_links(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->links);
	return (format_sizes->links + 1);
}

unsigned int	print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	if (format_data->align_user_left == true)
	{
		ft_buffercpy(&dest[offset], format_data->user);
	}
	else
	{
		offset += format_sizes->user - ft_strlen(format_data->user);	
		ft_buffercpy(&dest[offset], format_data->user);
		free(format_data->user);
		format_data->user = NULL;
	}
	return (format_sizes->user + 1);
}

unsigned int	print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	if (format_data->align_group_left == true)
	{
		ft_buffercpy(&dest[offset], format_data->group);
	}
	else
	{
		offset += format_sizes->group - ft_strlen(format_data->user);	
		ft_buffercpy(&dest[offset], format_data->group);
		free(format_data->group);
		format_data->group = NULL;
	}

		return (format_sizes->group + 1);
}

unsigned int	no_print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	(void)dest;
	(void)format_data;
	(void)format_sizes;
	(void)offset;

	return (0);
}

unsigned int	no_print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	(void)dest;
	(void)format_data;
	(void)format_sizes;
	(void)offset;

	return (0);
}

static unsigned int	print_format_size_field(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	if (format_data->mode[0] == 'c' || format_data->mode[0] == 'b')
	{
		return (print_format_device(dest, format_data, format_sizes, offset));
	}
	else
	{
		return (print_format_size(dest, format_data, format_sizes, offset));
	}
}

static unsigned int	print_format_size(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	unsigned int	buffer_size = ft_strlen(format_data->size);
	
	offset += format_sizes->size - buffer_size;
	ft_buffercpy(&dest[offset], format_data->size);
	offset += buffer_size + 1;
	
	return (format_sizes->size + 1);
}

static unsigned int	print_format_device(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	unsigned int	buffer_size = ft_strlen(format_data->major);
	offset += format_sizes->major - buffer_size;
	ft_buffercpy(&dest[offset], format_data->major);
	offset += buffer_size;

	ft_buffercpy(&dest[offset], ",");
	offset += 2;

	buffer_size = ft_strlen(format_data->minor);
	offset += format_sizes->minor - buffer_size;
	ft_buffercpy(&dest[offset], format_data->minor);
	offset += buffer_size + 1;

	return (format_sizes->size + 1);
}

static unsigned int	print_format_date(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->date);
	return (format_sizes->date + 1);
}

unsigned int	print_format_color(char *dest, t_format_data *format_data, unsigned int offset)
{

	const char *color = get_color_str(format_data->color);

	ft_buffercpy(&dest[offset], color);

	return (ft_strlen(color));
}

unsigned int	print_format_name(char *dest, t_format_data *format_data, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->name);
	return (ft_strlen(format_data->name));
}

unsigned int	print_format_color_reset(char *dest, unsigned int offset)
{
	ft_buffercpy(&dest[offset], RESET);

	return (RESET_SIZE);
}

unsigned int	print_format_short_ending(char *dest, unsigned int offset)
{
	int	shift = 0;

	dest[offset] = '\n';
	dest[offset + 1] = '\0';
	shift = 2;

	return (shift);
}

static unsigned int	print_format_long_ending(char *dest, t_format_data *format_data, unsigned int offset)
{
	int	shift = 0;

	if (format_data->mode[0] == 'l')
	{
		ft_buffercpy(&dest[offset + 1], "->");
		shift = 4;
		dest[offset + shift] = '\0';
	}
	else
	{
		shift = print_format_short_ending(dest, offset);
	}

	return (shift);
}

static void	print_format_symlink(t_format_data *format_data)
{
	if (format_data->target != NULL)
	{
		const char *color = get_color_str(format_data->target_color);
		ft_putstr_fd(color, 1);
		ft_putstr_fd(format_data->target, 1);
		ft_putstr_fd(RESET, 1);
		ft_putchar_fd('\n', 1);
	}
}

static	void space_feed(void *v, int n)
{
	int64_t	*s = (int64_t*)v;	

	int	r = n % 8;
	if (r != 0)
	{
		n += 8 - r;
	}
	n /= 8;
	for (int i = 0; i < n; ++i)
	{
		s[i] = 2314885530818453536;
	}
}

/*
static unsigned int get_end_pos(t_format_sizes *format_sizes)
{
  unsigned int  end_pos = 10;

  end_pos += format_sizes->mode;
  end_pos += format_sizes->links;
  end_pos += format_sizes->user;
  end_pos += format_sizes->group;
  end_pos += format_sizes->size;
  end_pos += format_sizes->minor;
  end_pos += format_sizes->major;
  end_pos += format_sizes->date;
  end_pos += format_sizes->name;
  end_pos += format_sizes->path;

  return (end_pos);
}*/
