/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:03 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 14:07:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool  sort_by_name(void *a, void *b)
{
  bool  ordered = true;
  t_data  *data_a = (t_data*)a;
  t_data  *data_b = (t_data*)b;
  
  if (ft_strcmp(data_a->name, data_b->name) > 0)
    ordered = false;
  return ordered;
}

bool  sort_by_name_reverse(void *a, void *b)
{
  bool  ordered = true;
  t_data  *data_a = (t_data*)a;
  t_data  *data_b = (t_data*)b;
  
  if (ft_strcmp(data_a->name, data_b->name) < 0)
    ordered = false;
  return ordered;
}
