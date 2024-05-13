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
static int  print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data);
static int print_format_data(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes);
static unsigned int format_mode(char *buffer, t_data *data);
static unsigned int format_links(char *buffer, t_data *data);
static unsigned int format_user(t_strategies *strat, char **buffer, t_data *data);
static unsigned int format_group(t_strategies *strat, char **buffer, t_data *data);
static unsigned int format_size(char *buffer, t_data *data);
static unsigned int format_minor(char *buffer, t_data *data);
static unsigned int format_major(char *buffer, t_data *data);
static unsigned int format_time(char *buffer, t_data *data);
static unsigned int format_recent_time(char *buffer, char *time_string);
static unsigned int format_late_time(char *buffer, char *time_string);
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
  print_path(dir->path);
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
      ret = print_all_format_data(strat, dir, &format_sizes, all_format_data);
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
    dir->total_block_size +=  data->block_nb * data->block_size;
    load_format_data(strat, data, format_sizes, &all_format_data[i]);
    entry = entry->next;
    ++i;
  }
  dir->total_block_size /= FT_LS_BLOCK_SIZE;
  set_max_size(&format_sizes->size, format_sizes->minor + format_sizes->major + 2);
  return (OK);
}

static int  load_format_data(t_strategies *strat, t_data *data, t_format_sizes *format_sizes, t_format_data *format_data)
{
  size_t  size = 0;
  
  size = format_mode(format_data->mode, data);
  set_max_size(&format_sizes->mode, size);
  size = format_links(format_data->links, data);
  set_max_size(&format_sizes->links, size);
  size = format_user(strat, &format_data->user, data);
  set_max_size(&format_sizes->user, size);
  size = format_group(strat, &format_data->group, data);
  set_max_size(&format_sizes->group, size);

  size = format_size(format_data->size, data);
  set_max_size(&format_sizes->size, size);
  size = format_minor(format_data->minor, data);
  set_max_size(&format_sizes->minor, size);
  size = format_major(format_data->major, data);
  set_max_size(&format_sizes->major, size);

  size = format_time(format_data->date, data);
  set_max_size(&format_sizes->date, size);

  format_data->name = data->name;
  size = ft_strlen(format_data->name);
  if (size > format_sizes->name)
  {
    format_sizes->name = size;
  }
  return (OK);
}

static unsigned int format_mode(char *buffer, t_data *data)
{
  unsigned int size = 10;
  char  types[] = {'-', 'd', 'c', 'b', 'p', 'l', 's'};
  buffer[0] = types[data->type];
  buffer[1] = (data->mode & S_IRUSR) ? 'r' : '-';
  buffer[2] = (data->mode & S_IWUSR) ? 'w' : '-';
  if (data->mode & S_ISUID)
  {
    buffer[3] = (data->mode & S_IXUSR) ? 's' : 'S';
  }
  else {
    buffer[3] = (data->mode & S_IXUSR) ? 'x' : '-';
  }
  buffer[4] = (data->mode & S_IRGRP) ? 'r' : '-';
  buffer[5] = (data->mode & S_IWGRP) ? 'w' : '-';
  if (data->mode & S_ISGID)
  {
    buffer[6] = (data->mode & S_IXGRP) ? 's' : 'S';
  }
  else {
    buffer[6] = (data->mode & S_IXGRP) ? 'x' : '-';
  }
  buffer[7] = (data->mode & S_IROTH) ? 'r' : '-';
  buffer[8] = (data->mode & S_IWOTH) ? 'w' : '-';
  if (data->mode & S_ISVTX)
  {
    buffer[9] = (data->mode & S_IXOTH) ? 't' : 'T';
  }
  else {
    buffer[9] = (data->mode & S_IXOTH) ? 'x' : '-';
  }
  if (data->xattr == true){
    ++size;
    buffer[10] = '+';
  }
  buffer[size] = '\0';
  return (size);
}

static unsigned int format_links(char *buffer, t_data *data)
{
  unsigned int  size = 0;
  size = ft_itoa_dec(data->links, buffer);
  return (size);
}

static unsigned int format_user(t_strategies *strat, char **buffer, t_data *data)
{
  *buffer = get_user_name(strat, data->uid);
  return (ft_strlen(*buffer));
}

static unsigned int format_group(t_strategies *strat, char **buffer, t_data *data)
{
  *buffer = get_group_name(strat, data->gid);
  return (ft_strlen(*buffer));
}

static unsigned int format_size(char *buffer, t_data *data)
{
  unsigned int  size = 0;
  if (!(data->type == CHR || data->type == BLK))
  {
    size = ft_itoa_dec(data->total_size, buffer);
  }
  return (size);
}

static unsigned int format_minor(char *buffer, t_data *data)
{
  unsigned int  size = 0;
  if (data->type == CHR || data->type == BLK)
  {
    size = ft_itoa_dec(minor(data->rdev), buffer);
  }
  return (size);
}

static unsigned int format_major(char *buffer, t_data *data)
{
  unsigned int  size = 0;
  if (data->type == CHR || data->type == BLK)
  {
    size = ft_itoa_dec(major(data->rdev), buffer);
  }
  return (size);
}

static unsigned int format_time(char *buffer, t_data *data)
{
  unsigned int  size = 0;
  errno = 0;
  char  *tmp = ctime(&data->time);
  if (tmp == NULL)
  {
    perror("ft_ls: ctime: ");
    return (0);
  }
  char  *time_string = ft_strdup(tmp);
  if (time_string == NULL)
  {
    return 0;
  }
  if (recent(time_string))
    size = format_recent_time(buffer, time_string);
  else {
    size = format_late_time(buffer, time_string);
  }
  return (size);
}

static unsigned int format_recent_time(char *buffer, char *time_string)
{
  ft_bufferncpy(&buffer[0], &time_string[4], 12);
  buffer[12] = '\0';
  return (12);
}

static unsigned int format_late_time(char *buffer, char *time_string)
{
  ft_bufferncpy(&buffer[0], &time_string[4], 7);
  ft_bufferncpy(&buffer[8], &time_string[20], 4);
  buffer[7]= ' ';
  buffer[12] = '\0';
  return (12);
}

static void set_max_size(unsigned int *max, unsigned int size)
{
  if (size > *max) {
    *max = size;
  }
}

static int  print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
  (void)strat;
  ft_putstr_fd("total: ", 1);
  ft_putnbr_fd(dir->total_block_size, 1);
  ft_putchar_fd('\n', 1);
  for(unsigned int i = 0; i < dir->entry_nb; ++i)
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
  unsigned int  buffer_size = 0;
  char  buffer[1024];
  ft_memset(buffer, ' ', end_pos);

  ft_buffercpy(&buffer[offset], format_data->mode);
  offset += format_sizes->mode + 1;
  
    ft_buffercpy(&buffer[offset], format_data->links);
    offset += format_sizes->links + 1;

    ft_buffercpy(&buffer[offset], format_data->user);
    offset += format_sizes->user + 1;

    ft_buffercpy(&buffer[offset], format_data->group);
    offset += format_sizes->group + 1;

  if(format_data->mode[0] == 'c' || format_data->mode[0] == 'b')
  {
    offset += format_sizes->minor - buffer_size;
    ft_buffercpy(&buffer[offset], format_data->minor);
    offset += buffer_size + 1;
  }
  else{
    buffer_size = ft_strlen(format_data->size);
    offset += format_sizes->size - buffer_size;
    ft_buffercpy(&buffer[offset], format_data->size);
    offset += buffer_size + 1;
  }
  
  ft_buffercpy(&buffer[offset], format_data->date);
  offset += format_sizes->date + 1;
  
  ft_buffercpy(&buffer[offset], format_data->name);
  offset += format_sizes->name;
  
  buffer[offset] = '\n';
  ++offset;
  buffer[offset] = '\0';
  write(1, buffer, offset + 1);
  return (OK);
}

static unsigned int get_end_pos(t_format_sizes *format_sizes)
{
  unsigned int  end_pos = 10;

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
