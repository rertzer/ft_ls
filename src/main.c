/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:44:08 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 11:44:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
  int           ret = OK;
  t_options     opt;
  t_strategies  strat;

  //read args: set options
  ret = set_options(&opt, argc, argv);
  if (ret != OK)
    return (ret);
    /*
  //set strategies
  ret = set_strategies(&opt, &strat);
  if (ret != OK)
    return (ret);
  */
  //foreach path in argv call list_path
  ret = list_all_path(&strat, argc, argv);
  return (ret);
}
