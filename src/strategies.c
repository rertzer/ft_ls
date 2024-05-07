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

int set_strategies(t_options *opt, t_strategies *strat)
{
  for (int i = 0; i < OPTIONS_NUMBER; ++i)
  {
    switch(opt->name[i])
    {
      case 'a':
        if (opt->value[i] == true){
          strat->keepEntry = keep_all;
        }
        else {
          strat->keepEntry = skip_dot;
        }
      case 'r':
        if (opt->value[i] == true){
          strat->sorting = sort_by_name_reverse;
        }
        else{
          strat->sorting = sort_by_name;
        }
        break;
      default:
        break;
    }
  }
  return OK;
}