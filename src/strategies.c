/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategies.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:54:45 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 10:54:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	option_a(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_A] == true)
	{
		strat->keepEntry = keep_all;
	}
	else
	{
		strat->keepEntry = skip_dot;
	}
}

void	option_l(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_L] == true)
	{
		strat->printallformat = print_all_format_data;
		strat->printformat = print_format_data_long;
		strat->isdirectory = is_directory_longlist;
		strat->printtotal = print_total;
	}
	else
	{
		strat->isdirectory = is_directory_simple;
	}
}

void	option_r(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_R] == true)
	{
		strat->sorting = sort_by_name_reverse;
	}
	else
	{
		strat->sorting = sort_by_name;
	}
}

void	option_R(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_RR] == true)
	{
		strat->recurse = recursive;
	}
	else
	{
		strat->recurse = no_recursion;
	}
}

void	option_t(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_T] == true)
	{
		option_time_sorting(strat, opt);
	}
}

void	option_time_sorting(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_R] == true)
	{
		strat->sorting = sort_by_name_reverse;
		strat->othersorting = sort_by_time_reverse;
	}
	else
	{
		strat->sorting = sort_by_name;
		strat->othersorting = sort_by_time;
	}
}
