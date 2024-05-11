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
static void init_format_sizes(t_format_sizes *format_sizes);
static int  load_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data * all_format_data);
static int  load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data);
static int  print_all_format_data(t_strategies *strat, unsigned int entry_nb, t_format_sizes *format_sizes, t_format_data *all_format_data);
static int print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes);
static unsigned int format_mode(char *buffer, e_type type, mode_t mode);
static void set_max_size(unsigned int *max, unsigned int size);
static unsigned int get_end_pos(t_format_sizes *format_sizes);

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
  int ret = OK;
  previous_print(strat);
  t_format_sizes  format_sizes;
  init_format_sizes(&format_sizes);
  errno =  0;
  t_format_data *all_format_data = malloc(sizeof(t_format_data) * dir->entry_nb);
  if (all_format_data == NULL)
  {
    ret = MAJOR_KO;
  }
  else {
    ret = load_all_format_data(strat, dir, &format_sizes, all_format_data);
    if (ret == OK){
      ret = print_all_format_data(strat, dir->entry_nb, &format_sizes, all_format_data);
    }
  }
  return (ret);
}

static int  load_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data * all_format_data)
{
  int i = 0;
  t_list *entry = dir->content;
  while (entry != NULL)
  {
    t_data  *data = (t_data*)entry->content;
    load_format_data(strat, data, format_sizes, &all_format_data[i]);
    entry = entry->next;
    ++i;
  }
  return (OK);
}

static int  load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
  (void)strat;
  size_t  size = 0;
  
  size = format_mode(format_data->mode, data->type, data->mode);
  set_max_size(&format_sizes->mode, size);
  format_data->name = data->name;
  size = ft_strlen(format_data->name);
  if (size > format_sizes->name)
  {
    format_sizes->name = size;
  }
  return (OK);
}
/*
 *i         S_ISUID     04000   set-user-ID bit (see execve(2))
           S_ISGID     02000   set-group-ID bit (see below)
           S_ISVTX     01000   sticky bit (see below)

           S_IRWXU     00700   owner has read, write, and execute
                               permission
           S_IRUSR     00400   owner has read permission
           S_IWUSR     00200   owner has write permission
           S_IXUSR     00100   owner has execute permission

           S_IRWXG     00070   group has read, write, and execute
                               permission
           S_IRGRP     00040   group has read permission
           S_IWGRP     00020   group has write permission
           S_IXGRP     00010   group has execute permission

           S_IRWXO     00007   others (not in group) have read, write,
                               and execute permission
           S_IROTH     00004   others have read permission
           S_IWOTH     00002   others have write permission
           S_IXOTH     00001 
*/
static unsigned int format_mode(char *buffer, e_type type, mode_t mode)
{
  unsigned int size = 2;
  char  types[] = {'-', 'd', 'c', 'b', 'p', 'l', 's'};
  buffer[0] = types[type];
  buffer[1] = (mode & S_IRUSR) ? 'r' : '-';
  buffer[2] = '\0';
  return (size);
}

static void set_max_size(unsigned int *max, unsigned int size)
{
  if (size > *max) {
    *max = size;
  }
}

static int  print_all_format_data(t_strategies *strat, unsigned int entry_nb, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
  (void)strat;
  
  for(unsigned int i = 0; i < entry_nb; ++i)
  {
    print_format_data(strat, &all_format_data[i], format_sizes);
  }
  return (OK);
}

static int print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes)
{
  (void)strat;
  unsigned int  end_pos = get_end_pos(format_sizes);
  unsigned int  offset = 0;
  char  buffer[1024];
  ft_memset(buffer, ' ', end_pos);
  ft_buffercpy(&buffer[offset], format_data->mode);
  offset += format_sizes->mode + 1;
  ft_buffercpy(&buffer[offset], format_data->name);
  offset += format_sizes->name + 1;
  buffer[offset] = '\n';
  ++offset;
  buffer[offset] = '\0';
  write(1, buffer, offset + 1);
  return (OK);
}

static unsigned int get_end_pos(t_format_sizes *format_sizes)
{
  unsigned int  end_pos = 9;

  end_pos += format_sizes->mode;
  end_pos += format_sizes->links;
  end_pos += format_sizes->user;
  end_pos += format_sizes->group;
  end_pos += format_sizes->size;
  end_pos += format_sizes->minor;
  end_pos += format_sizes->major;
  end_pos += format_sizes->date;
  end_pos += format_sizes->name;
  end_pos += format_sizes->path;

  return (end_pos);
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

static void init_format_sizes(t_format_sizes *format_sizes)
{
  format_sizes->mode = 0;
  format_sizes->links = 0;
  format_sizes->user = 0;
  format_sizes->group = 0;
  format_sizes->size = 0;
  format_sizes->minor = 0;
  format_sizes->major = 0;
  format_sizes->date = 0;
  format_sizes->name = 0;
  format_sizes->path = 0;
  }
