/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_set_strategies.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:37:30 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 10:37:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int set_strategies(t_options *opt, t_strategies *strat)
{
	strat->addlist = ft_lstadd_front;
	strat->sortingalgo = bubble_sort;
	strat->setTime = last_modif;
	strat->printtotal = no_print_total;
	strat->previous_print = false;
	strat->print_path_name = true;
	strat->printuser = print_format_user;
	strat->printgroup = print_format_group;
	strat->color = no_color;

 	option_a(strat, opt);
	option_l(strat, opt);
	option_r(strat, opt);
	option_R(strat, opt);
	option_t(strat, opt);

	return OK;
}

