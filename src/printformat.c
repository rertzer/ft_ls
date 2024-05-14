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

static int print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes);
static unsigned int	print_format_mode(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
static unsigned int get_end_pos(t_format_sizes *format_sizes);

int  print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
  for(unsigned int i = 0; i < dir->entry_nb; ++i)
  {
    print_format_data(strat, &all_format_data[i], format_sizes);
  }
  return (OK);
}

static int print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes)
{
	(void)strat;
	unsigned int  end_pos = get_end_pos(format_sizes);
	unsigned int  offset = 0;
	unsigned int  buffer_size = 0;
	char  buffer[1024];

	ft_memset(buffer, ' ', end_pos);

	offset += print_format_mode(buffer, format_data, format_sizes, offset);

	ft_buffercpy(&buffer[offset], format_data->links);
	offset += format_sizes->links + 1;

	ft_buffercpy(&buffer[offset], format_data->user);
	offset += format_sizes->user + 1;

	ft_buffercpy(&buffer[offset], format_data->group);
	offset += format_sizes->group + 1;

	if(format_data->mode[0] == 'c' || format_data->mode[0] == 'b')
	{
		buffer_size = ft_strlen(format_data->major);
		offset += format_sizes->major - buffer_size;
		ft_buffercpy(&buffer[offset], format_data->major);
		offset += buffer_size;

		ft_buffercpy(&buffer[offset], ",");
		offset += 2;

		buffer_size = ft_strlen(format_data->minor);
		offset += format_sizes->minor - buffer_size;
		ft_buffercpy(&buffer[offset], format_data->minor);
		offset += buffer_size + 1;
	}
	else
	{
		buffer_size = ft_strlen(format_data->size);
		offset += format_sizes->size - buffer_size;
		ft_buffercpy(&buffer[offset], format_data->size);
		offset += buffer_size + 1;
	}

	ft_buffercpy(&buffer[offset], format_data->date);
	offset += format_sizes->date + 1;

	ft_buffercpy(&buffer[offset], format_data->name);
	offset += format_sizes->name;

	buffer[offset] = '\n';
	++offset;
	buffer[offset] = '\0';
	write(1, buffer, offset + 1);
	return (OK);
}

static unsigned int	print_format_mode(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset)
{
	ft_buffercpy(&dest[offset], format_data->mode);
	return (format_sizes->mode + 1);
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


