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

static int			print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes);
static unsigned int	print_format_mode(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_links(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_size_field(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_size(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_device(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_date(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int	print_format_name(char *dest, t_format_data *format_data, unsigned int offset);
static unsigned int	print_format_ending(char *dest, t_format_data *format_data, unsigned int offset);
static void			print_format_symlink(t_format_data *format_data);
static unsigned int	get_end_pos(t_format_sizes *format_sizes);

int	print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	for (unsigned int i = 0; i < dir->entry_nb; ++i)
	{
		print_format_data(strat, &all_format_data[i], format_sizes);
	}

	return (OK);
}

static int	print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes)
{
	(void)strat;
	unsigned int	end_pos = get_end_pos(format_sizes);
	unsigned int	offset = 0;
	char			buffer[1024];

	ft_memset(buffer, ' ', end_pos);

	offset += print_format_mode(buffer, format_data, format_sizes, offset);
	offset += print_format_links(buffer, format_data, format_sizes, offset);
	offset += print_format_user(buffer, format_data, format_sizes, offset);
	offset += print_format_group(buffer, format_data, format_sizes, offset);
	offset += print_format_size_field(buffer, format_data, format_sizes, offset);
	offset += print_format_date(buffer, format_data, format_sizes, offset);
	offset += print_format_name(buffer, format_data, offset);
	offset += print_format_ending(buffer, format_data, offset);

	write(1, buffer, offset);
	print_format_symlink(format_data);

	return (OK);
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

static unsigned int	print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->user);
	return (format_sizes->user + 1);
}

static unsigned int	print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->group);
	return (format_sizes->group + 1);
}

static unsigned int	print_format_size_field(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	if(format_data->mode[0] == 'c' || format_data->mode[0] == 'b')
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

static unsigned int	print_format_name(char *dest, t_format_data *format_data, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->name);
	return (ft_strlen(format_data->name));
}

static unsigned int	print_format_ending(char *dest, t_format_data *format_data, unsigned int offset)
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
		dest[offset] = '\n';
		dest[offset + 1] = '\0';
		shift = 2;
	}

	return (shift);
}

static void	print_format_symlink(t_format_data *format_data)
{
	if (format_data->target != NULL)
	{
		ft_putstr_fd(format_data->target, 1);
		ft_putchar_fd('\n', 1);
	}
}

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
}
