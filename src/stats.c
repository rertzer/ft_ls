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

int add_stats(t_strategies *strat, char *path, t_data *data)
{
  int ret = OK;
  struct stat stat_buffer;
    
  errno = 0;
  if (lstat(path, &stat_buffer) != 0) {
    ret = MAJOR_KO;
    ft_putstr_fd("ft_ls: lstat: ", 2);
    perror(path);
  }
  else {
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
