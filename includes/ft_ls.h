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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>

#include "../libft/libft.h"

# define  OK 0
# define  MINOR_KO 1
# define  MAJOR_KO 2

//mandatory
# define OPTIONS_NUMBER 5

typedef struct {
  char  name[OPTIONS_NUMBER];
  bool  value[OPTIONS_NUMBER];
} t_options;

typedef struct
{
  char  name[256];
}  t_file_data;

typedef struct
{
  int (*sorting)(t_file_data);
  int (*setTime)(t_file_data);
}  t_strategies;

// option handler
int set_options(t_options *opt, int argc, char **argv);
int set_strategies(t_options *opt, t_strategies *strat);
// list_path
int list_all_path(t_strategies *strat, int argc, char **argv);
int list_path(t_strategies *strats, char* path);
// directory content
int get_dir_content(t_strategies *strat, t_list **dir_content, char *path);
// error handling
void  print_char_error(char *message, char param);


#endif
