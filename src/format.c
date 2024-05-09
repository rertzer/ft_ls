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

static void  previous_print(t_strategies *strat);

int simple(t_strategies *strat, t_directory *dir)
{
  int ret = OK;
  t_list *lst = dir->content;
  previous_print(strat);
  print_path(dir->path);
  while (lst)
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
  (void)dir;
  previous_print(strat);
  int ret = OK;
  return (ret);
}

static void  previous_print(t_strategies *strat)
{
  if (strat->previous_print)
    {
      ft_putchar_fd('\n', 1);
    }
    else{
      strat->previous_print = true;
    }
}

void  print_path(char *path)
{
  if (path != NULL && ft_strcmp(path, "."))
  {
    ft_putstr_fd(path, 1);
    ft_putstr_fd(":\n", 1);
  }
}
