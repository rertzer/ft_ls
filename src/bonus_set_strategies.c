/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_set_strategies.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:37:49 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 10:37:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

int set_strategies(t_options *opt, t_strategies *strat)
{
	strat->settime = last_modif;
	strat->othersorting = NULL;
	strat->printtotal = no_print_total;		
	strat->printallformat = print_all_format_data_column;
	strat->printformat = print_format_data_short;
	strat->previous_print = false;
	strat->print_path_name = true;
	strat->strcmp = ft_strcmp_local;

 	option_a(strat, opt);

	option_l(strat, opt);
	option_d(strat, opt);
	
	option_R(strat, opt);

	option_f(strat, opt);
	option_t(strat, opt);
	option_r(strat, opt);
	option_g(strat, opt);
	option_G(strat, opt);
	option_u(strat, opt);
	option_color(strat, opt);

	return OK;
}

