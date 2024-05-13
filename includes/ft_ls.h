/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:20:47 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 10:20:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*debug */
#include <stdio.h>

/*------*/

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>

#include "../libft/libft.h"

# define  OK 0
# define  MINOR_KO 1
# define  MAJOR_KO 2

//mandatory
# define OPTIONS_NUMBER 5
# define MODES_NB 7
# define HASH_SIZE 512
# define HASH_A 2654435769
# define HASH_SHIFT 23

typedef enum {REG, DIREC, CHR, BLK, FIFO, LNK, SOCK} e_type; 

typedef struct {
  char  name[OPTIONS_NUMBER];
  bool  value[OPTIONS_NUMBER];
} t_options;

typedef struct {
  unsigned int  id;
  char *        value;
} t_id;

typedef struct {
  e_type  type;
  dev_t   dev;
  dev_t   rdev;
  bool    xattr;
  mode_t  mode;
  nlink_t links;
  uid_t   uid;
  gid_t   gid;
  size_t  total_size;
  size_t  block_size;
  size_t  block_nb;
  time_t  time;
  char    *name;
  char    *path;
}  t_data;

typedef struct {
  char  mode[12];
  char  links[20];
  char  *user;
  char  *group;
  char  size[20];
  char  minor[11];
  char  major[11];
  char  date[13];
  char  *name;
  char  *path;
} t_format_data;

typedef struct {
  unsigned int  mode;
  unsigned int  links;
  unsigned int  user;
  unsigned int  group;
  unsigned int  size;
  unsigned int  minor;
  unsigned int  major;
  unsigned int  date;
  unsigned int  name;
  unsigned int  path;
} t_format_sizes;

typedef struct {
  char  *path;
  unsigned int  entry_nb;
  t_list *content;
} t_directory;

typedef struct s_strategies {
  bool (*keepEntry)(struct dirent*);
  bool (*sorting)(void *, void *);
  time_t (*setTime)(struct stat*);
  int (*recurse)(struct s_strategies*, t_directory*);
  int (*format)(struct s_strategies*, t_directory*);
  bool  default_path;
  bool  previous_print;
  t_list* users[HASH_SIZE];
  t_list* groups[HASH_SIZE];
}  t_strategies;


// data handling
int add_new_data(t_list **lst, char const * const name, char const * const path);
t_data  *new_data();
void  data_del(void*);
// option handler
int   parse_all_args(t_options *opt, t_list **paths, int argc, char **argv);
bool  get_option(t_options *opt, char arg);
//strategies
int set_strategies(t_options *opt, t_strategies *strat);
//sorting
int   bubble_sort(t_list* list, bool(*sorting)(void*, void*));
bool  sort_by_name(void *a, void *b);
bool  sort_by_name_reverse(void *a, void *b);
//keepentry
bool  keep_all(struct dirent* entry);
bool  skip_dot(struct dirent* entry);
//recursion
int no_recursion(t_strategies *strat, t_directory *dir);
int recursive(t_strategies *strat, t_directory *dir);
// formating
int longlist(t_strategies *strat, t_directory *dir);
int simple(t_strategies *strat, t_directory *dir);
void  print_path(char *path);
// list_path
int  default_path(t_strategies *strat);
int list_all_files(t_strategies *strat, t_list **all_paths);
int list_all_path(t_strategies *strat, t_list *all_paths);
int list_path(t_strategies *strats, char* path);
//directory
void  free_directory(t_directory *dir);
// directory content
void  init_dir(t_directory *dir);
int get_dir_content(t_strategies *strat, t_directory *dir);
// time
time_t  last_modif(struct stat *stat_buffer);
// stats
int add_all_stats(t_strategies *strat, t_list *all_paths);
int add_stats(t_strategies *strat, t_data *data);
int  compute_stats(t_strategies *strat, t_data *data);
// dictonnary
int insert_key(t_list *dict[HASH_SIZE], unsigned int key, char *value);
char* get_value_by_key(t_list *dict[HASH_SIZE], unsigned int key);
void  init_dict(t_list *dict[HASH_SIZE]);
void  free_dict(t_list *dict[HASH_SIZE]);
//ids
void  init_ids(t_strategies *strat);
void  free_ids(t_strategies *strat);
char *get_user_name(t_strategies *strat, uid_t id);
char *get_group_name(t_strategies *strat, gid_t id);
// error handling
void  print_char_error(char *message, char param);
#endif
