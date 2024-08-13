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

static int	loop_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data);
static int					load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data);
static inline void			load_block_size(t_directory *dir, t_data *data);
static void	compute_block_size(t_directory *dir);
static void	compute_size_size(t_format_sizes *format_sizes);

int  load_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	int		ret = OK;

	loop_all_format_data(strat, dir, format_sizes, all_format_data);
	compute_block_size(dir);
	compute_size_size(format_sizes);

	return (ret);
}

static int	loop_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	int		ret = OK;
	int		i = 0;

	for (t_list *entry = dir->content; entry != NULL;entry = entry->next, ++i)
	{
		t_data	*data = (t_data*)entry->content;

		load_block_size(dir, data);
		ret = load_format_data(strat, data, format_sizes, &all_format_data[i]);
		if (ret == INTERNAL_KO)
		{
			break;
		}
	}

	return (ret);
}

static inline void	load_block_size(t_directory *dir, t_data *data)
{
	dir->total_block_size +=  data->block_nb;
}

static int	load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
	if (data->file.mode == UINT_MAX)
	{
		return (load_format_data_invalid(strat, data, format_sizes, format_data));
	}
	else
	{
		return (load_format_data_valid(strat, data, format_sizes, format_data));
	}
}

static void	compute_block_size(t_directory *dir)
{
	dir->total_block_size = (dir->total_block_size + 1) / 2;
}

static void	compute_size_size(t_format_sizes *format_sizes)
{
	if (format_sizes->minor || format_sizes->major)
	{
		set_max_size(&format_sizes->size, format_sizes->minor + format_sizes->major + 2);
	}
}

void set_max_size(unsigned int *max, unsigned int size)
{
	if (size > *max)
	{
		*max = size;
	}
}
