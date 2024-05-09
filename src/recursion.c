/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:22:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 14:22:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int no_recursion(t_strategies *strat, t_directory *dir)
{
  (void)strat;
  (void)dir;
  return (OK);
}

int recursive(t_strategies *strat, t_directory *dir)
{
  t_list  *lst = dir->content;
  int ret = OK;
  bool  first = true;
  while (lst)
  {
    t_data *data = (t_data*)lst->content;
    if (data->type == DIREC)
    {
      char *path = ft_strdup(data->path);
      if (path == NULL)
      {
        ret = MAJOR_KO;
        break;
      }
      if (first){
        first = false;
      }
      else{
        ft_putchar_fd('\n', 1);
      }
      print_path(path);
      ret = list_path(strat, path);
      if (ret != OK)
        break;
    }
    lst = lst->next;
  }
  return (ret);
}
