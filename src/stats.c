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
/*
typedef struct
{
  e_type  type;
  mode_t  mode;
  nlink_t links;
  uid_t   uid;
  git_t   gid;
  size_t  total_size;
  size_t  block_size;
  size_t  block_nb;
  t_time  time;
  char    name[256];
}  t_data;
*/

int add_stats(t_strategies *strat, t_data *data)
{
  int ret = OK;
  struct stat = stat_buffer;
    
  errno = 0;
  if (lstat(data->name, &stat_buffer) != 0) {
    ret = MAJOR_KO;
    perror("ft_ls: lstat: ");
  }
  else {
    data->mode = stat_buffer->st_mode;
    data->uid = stat_buffer->st_uid;
    data->git = stat_buffer->st_gid;
    data->total_size = stat_buffer->st_size;
    data->block_size = stat_buffer->blksize;
    data->block_nb = stat_buffer->st_blocks;
    data->time = strat->getTime(stat_buffer);
  }
  return (ret);
}
