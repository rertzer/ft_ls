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

static int add_entry(t_strategies *strat, t_list **dir_content, struct dirent *dir_entry);

int get_dir_content(t_strategies *strat, t_list **dir_content, char *path)
{
  int ret = OK;
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
      errno = 0;
      dir_entry = readdir(dir_stream);
      if (dir_entry == NULL)
        break;
      if (strat->keepEntry(dir_entry))
      {
        ret = add_entry(strat, dir_content, dir_entry);
        if (ret != OK)
          break;
      }
    }
    if (errno != 0 && ret == OK) //readdir error
      {
        ret = MAJOR_KO;
        perror("ft_ls: readdir: ");
      }
  }
  closedir(dir_stream);
  return (ret);
}
     
static int add_entry(t_strategies *strat, t_list **dir_content, struct dirent *dir_entry)
{
  (void)strat;
  t_list  *newlst = NULL;

  errno = 0;
  t_data *data = malloc(sizeof(t_data));
  if (data == NULL)
  {
    perror("ft_ls: malloc: ");
    return (MAJOR_KO);
  }
  ft_strcpy(data->name, dir_entry->d_name);
  errno = 0;
  newlst = ft_lstnew(data);
  if (newlst == NULL)
  {
    perror("ft_ls: malloc: ");
    free(data);
    return (MAJOR_KO);
  }
  ft_lstadd_front(dir_content, newlst);
  return (OK);
}
