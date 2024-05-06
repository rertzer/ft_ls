/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dircontent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:50:14 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 15:50:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int read_entry(t_startegies *strat, t_list **dir_content, struct dirent *dir_entry);

int get_dir_content(t_startegies *strat, t_list **dir_content, char *path)
{
  int ret = OK;
  t_list  *newlist = NULL;
  struct dirent *dir_entry = NULL;
  errno = 0;
  DIR *dir_stream = opendir(path);
  if (dir_stream == NULL)
  {
    perror("ft_ls: opendir: ");
    ret = MINOR_KO;
  }
  else {
    while (true)
    {
      dir_entry = readdir(dir_stream);
      if (dir_entry == NULL)
        break;
      ret = read_entry(strat, dir_content, dir_entry);
      if (ret != OK)
        break;
    }
  }
  return (ret);
}
     
static int read_entry(t_startegies *strat, t_list **dir_content, struct dirent *dir_entry)
{
  t_file_data *data = malloc(sizeof(t_file_data));
  if (data == NULL)
    break;

}
