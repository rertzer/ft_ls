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
  if(get_option(opt, 'a'))
  {
    strat->keepEntry = keep_all;
  }
  else {
    strat->keepEntry = skip_dot;
  }
  return OK;
}
