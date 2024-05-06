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

int list_all_path(t_strategies *strat, int argc, char **argv)
{
  int   ret = OK;
  char  *path = NULL;

  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] != '-')
    {
      errno = 0;
      path = ft_strdup(argv[i]);
      if (path == NULL)
      {
        perror("ft_ls: malloc: ");
        ret = MAJOR_KO;
        break;
      }
      ret = list_path(strat, path);
      if (ret != OK)
        break;
    }
  }
  return (ret);
}

int list_path(t_strategies *strat, char* path)
{
  (void)strat;
  int ret = OK;
  t_list  *dir_content = NULL;
  printf("path is %s\n", path);
  ret = get_dir_content(strat, &dir_content, path);
  if (ret = OK)
  {}
  free(path);
  return (ret);
}
