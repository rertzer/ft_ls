/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathlisting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:17:53 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 15:17:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int  default_path(t_strategies *strat);

int list_all_path(t_strategies *strat, t_list *all_paths)
{
  int   ret = OK;
  char  *path = NULL;
  bool  path_exist = false;

  while (all_paths != NULL)
  {
    t_data  *data = (t_data*)all_paths->content;
    path = ft_strdup(data->path);
    if (path == NULL)
    {
      ret = MAJOR_KO;
      break;
    }
    if (path_exist == true)
      ft_putchar_fd('\n', 1);
    print_path(path);
    ret = list_path(strat, path);
    if (ret != OK)
      break;
    path_exist = true;
    all_paths = all_paths->next;
  }
  if (path_exist == false && ret == OK)
  {
    ret = default_path(strat);
  }

  return (ret);
}

static int  default_path(t_strategies *strat)
{
  int ret = OK;
  char  *path = strdup(".");
  if (path == NULL)
  {
    ret = MAJOR_KO;
  }
  else {
    ret = list_path(strat, path);
  }
  return (ret);
}

int list_path(t_strategies *strat, char* path)
{
  int ret = OK;
  t_directory dir;
  dir.path = path;
  dir.content = NULL;

  ret = get_dir_content(strat, &dir);
  if (ret == OK)
  {
    bubble_sort(dir.content, strat->sorting);
    strat->format(strat, &dir);
      }
  ret = strat->recurse(strat, &dir);
  free_directory(&dir);
  return (ret);
}
