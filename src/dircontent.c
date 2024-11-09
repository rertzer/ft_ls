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

static DIR *get_dir_stream(t_directory *dir);
static int add_dir_entries(t_strategies *strat, t_directory *dir,
                           DIR *dir_stream);
static int add_entry(t_strategies *strat, t_directory *dir,
                     struct dirent *dir_entry);

int get_dir_content(t_strategies *strat, t_directory *dir) {
  int ret = OK;

  DIR *dir_stream = get_dir_stream(dir);
  if (dir_stream == NULL) {
    ret = MINOR_KO;
  } else {
    ret = add_dir_entries(strat, dir, dir_stream);
    if (errno != 0 && ret == OK) {
      ret = print_perror_msg("cannot read directory '", dir->path);
      dir->valid = false;
    }
  }
  closedir(dir_stream);

  return (ret);
}

static DIR *get_dir_stream(t_directory *dir) {
  errno = 0;
  DIR *dir_stream = opendir(dir->path);
  if (dir_stream == NULL) {
    print_perror_msg("cannot open directory '", dir->path);
    dir->valid = false;
  }

  return (dir_stream);
}

static int add_dir_entries(t_strategies *strat, t_directory *dir,
                           DIR *dir_stream) {
  int ret = OK;
  int status = ret;
  struct dirent *dir_entry = NULL;

  while (true) {
    errno = 0;
    dir_entry = readdir(dir_stream);
    if (dir_entry == NULL) {
      break;
    }
    if (strat->keepEntry(dir_entry)) {
      ret = add_entry(strat, dir, dir_entry);
      status = worst(status, ret);
      if (ret == INTERNAL_KO) {
        break;
      }
    }
  }

  return (status);
}

static int add_entry(t_strategies *strat, t_directory *dir,
                     struct dirent *dir_entry) {
  int ret = INTERNAL_KO;

  t_data *data = add_new_data(&dir->content, dir_entry->d_name,
                              dir_entry->d_type, dir->path, strat->addlist);

  if (data != NULL) {
    ++dir->entry_nb;
    ret = add_stats(strat, data);
  }

  return (ret);
}
