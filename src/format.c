/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:32:07 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 15:32:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int simple(t_strategies *strat, t_directory *dir)
{
  (void)strat;
  int ret = OK;
  t_list *lst = dir->content;
  while(lst)
  {
    t_data* d = (t_data*)lst->content;
    ft_putstr_fd(d->name, 1);
    ft_putchar_fd('\n', 1);
    lst = lst->next;
  }

  return (ret);
}

int longlist(t_strategies *strat, t_directory *dir)
{
  (void)strat;
  (void)dir;
  int ret = OK;
  return (ret);
}

void  print_path(char *path)
{
  ft_putstr_fd(path, 1);
  ft_putstr_fd(":\n", 1);
}
