/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_strategies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:01:49 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 11:01:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	option_d(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_D] == true)
	{
		strat->isdirectory = is_directory_nodir;
	}
}

void	option_f(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_F] == true)
	{
		strat->keepEntry = keep_all;
		strat->addlist = ft_lstadd_back;
		strat->sortingalgo = no_sorting;
	}
	else
	{
		strat->addlist = ft_lstadd_front;
		strat->sortingalgo = bubble_sort;
	}

}

void	option_g(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_G] == true)
	{
		strat->printuser = no_print_format_user;
	}
	else
	{
		strat->printuser = print_format_user;
	}
}

void	option_G(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_GG] == true)
	{
		strat->printgroup = no_print_format_group;
	}
	else
	{
		strat->printgroup = print_format_group;
	}
}
		
void	option_u(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_U] == true)
	{
		strat->settime = access_time;

		if (!((opt->value[OPT_L] == true && opt->value[OPT_T] == false)))
		{
			option_time_sorting(strat, opt);
		}
	}
}

void	option_color(t_strategies *strat, t_options *opt)
{
	if (opt->value[OPT_COLOR] == true)
	{
		strat->color = format_color;
	}
	else
	{
		strat->color = no_color;
	}
}
