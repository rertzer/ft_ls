/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:32:07 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 15:32:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_directory(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data);
static void	previous_print(t_strategies *strat);
static void	print_path(t_strategies *strat, char *path);
static void	init_format_sizes(t_format_sizes *format_sizes);

int format(t_strategies *strat, t_directory *dir)
{
	int 			ret = INTERNAL_KO;
	t_format_sizes  format_sizes;

	init_format_sizes(&format_sizes);
	t_format_data *all_format_data = ft_malloc(sizeof(t_format_data) * dir->entry_nb);

	if (all_format_data != NULL)
	{
		ret = load_all_format_data(strat, dir, &format_sizes, all_format_data);
		if (ret == OK && dir->valid == true)
		{
			ret = print_directory(strat, dir, &format_sizes, all_format_data);
		}
		free(all_format_data);
	}
	return (ret);
}

static int	print_directory(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	previous_print(strat);
	print_path(strat, dir->path);
	strat->printtotal(dir);
	int		ret = strat->printallformat(strat, dir, format_sizes, all_format_data);
	return (ret);
}

static void init_format_sizes(t_format_sizes *format_sizes)
{
	format_sizes->mode = 0;
	format_sizes->links = 0;
	format_sizes->user = 0;
	format_sizes->group = 0;
	format_sizes->size = 0;
	format_sizes->minor = 0;
	format_sizes->major = 0;
	format_sizes->date = 0;
	format_sizes->name = 0;
	format_sizes->path = 0;
}

static void  previous_print(t_strategies *strat)
{
	if (strat->previous_print)
	{
		ft_putchar_fd('\n', 1);
	}
	else
	{
		strat->previous_print = true;
	}
}

static void  print_path(t_strategies *strat, char *path)
{
	if (path != NULL && strat->print_path_name == true)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd(":\n", 1);
	}
}

void	print_total(t_directory *dir)
{
	if (dir->path != NULL)
	{
		ft_putstr_fd("total ", 1);
		ft_putnbr_fd(dir->total_block_size, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	no_print_total(t_directory *dir)
{
	(void)dir;
}
