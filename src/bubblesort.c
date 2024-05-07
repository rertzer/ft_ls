/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:30:23 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 13:30:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int bubble_sort(t_list *lst, bool(*ordered)(void *a, void *b))
{
  bool    sorted = false;
  void    *tmp = NULL;
  t_list  *current = lst;
  while (sorted == false)
  {
    sorted = true;
    current = lst;
    while(current)
    {
      if (current->next && ! ordered(current->content, current->next->content))
      {
        tmp = current->content;
        current->content = current->next->content;
        current->next->content = tmp;
        sorted = false;
      }
     current = current->next;
    }
  }
  return (OK);
}
