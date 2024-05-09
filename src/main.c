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
  t_list        *all_paths = NULL;
  t_strategies  strat;

  //read args: set options
  ret = parse_all_args(&opt, &all_paths, argc, argv);
  if (ret != OK)
    return (ret);
   
  //set strategies
  ret = set_strategies(&opt, &strat);
  if (ret != OK)
  {
    ft_lstclear(&all_paths, data_del);
    return (ret);
  }
  init_ids(&strat);
  ret = add_all_stats(&strat, all_paths);
  if (ret == OK){
    bubble_sort(all_paths, strat.sorting);

    //foreach path in argv call list_path
    ret = list_all_path(&strat, all_paths);
  }
  ft_lstclear(&all_paths, data_del);
  free_ids(&strat);
  return (ret);
}
