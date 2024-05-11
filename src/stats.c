/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:50:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 15:51:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int set_type(t_data *data);


int add_all_stats(t_strategies *strat, t_list *all_paths)
{
  int ret = OK;
  t_data  *data = NULL;
  while (all_paths != NULL)
  {
    data = (t_data*)all_paths->content;
    ret = add_stats(strat, data);
    if (ret != OK)
      break;
    ret = compute_stats(strat, data);
    if (ret != OK)
      break;
    all_paths = all_paths->next;
  }
  return (ret);
}

int add_stats(t_strategies *strat, t_data *data)
{
  int ret = OK;
  struct stat stat_buffer;
    
  errno = 0;
  if (lstat(data->path, &stat_buffer) != 0) {
    ret = MAJOR_KO;
    ft_putstr_fd("ft_ls: lstat: ", 2);
    perror(data->path);
  }
  else {
    data->dev = stat_buffer.st_dev;
    data->mode = stat_buffer.st_mode;
    data->uid = stat_buffer.st_uid;
    data->gid = stat_buffer.st_gid;
    data->total_size = stat_buffer.st_size;
    data->block_size = stat_buffer.st_blksize;
    data->block_nb = stat_buffer.st_blocks;
    data->time = strat->setTime(&stat_buffer);
  }
  return (ret);
}

int  compute_stats(t_strategies *strat, t_data *data)
{
  (void)strat;
  int ret = OK;
  ret = set_type(data);
  //if (ret != OK)
    return (ret);
}

static int set_type(t_data *data)
{
  int ret = MAJOR_KO;
  
  mode_t const modes[] = {S_IFREG, S_IFDIR, S_IFCHR, S_IFBLK, S_IFIFO, S_IFLNK, S_IFSOCK};
  mode_t  type = data->mode & S_IFMT;
  for (int i = 0; i < MODES_NB; ++i)
  {
    if(type == modes[i])
    {
      data->type = i;
      ret = OK;
      break;
    }
  }
  if (ret != OK)
  {
    ft_putstr_fd("ft_ls: ", 2);
    ft_putstr_fd(data->name, 2);
    ft_putstr_fd(": invalid file type\n", 2);
  }
  return (ret); 
}
