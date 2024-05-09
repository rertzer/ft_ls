/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:15:05 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 13:15:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void init_options(t_options *opt);
static int  parse_arg(t_options *opt, t_list **paths, char *arg);
static int  parse_option(t_options *opt, char arg);

int parse_all_args(t_options *opt, t_list **paths, int argc, char **argv)
{
  int ret = OK;
  init_options(opt);
  for (int i = 1; i < argc; ++i)
  {
    ret = parse_arg(opt, paths, argv[i]);
    if (ret != OK)
      break;
  }
  return (ret);
}

static void  init_options(t_options *opt)
{
  char  tmp[] = {'a', 'l', 'r', 'R', 't'};

  for (int i = 0; i < OPTIONS_NUMBER; ++i)
  {
    opt->name[i] = tmp[i];
    opt->value[i] = false;
  }
}

static int  parse_arg(t_options *opt, t_list **paths, char *arg)
{
  int ret = OK;

  if (arg == NULL)
    return (ret);
  
  if (arg[0] == '-')
  {
    for (int i = 1; arg[i] != '\0'; ++i)
    {
      ret = parse_option(opt, arg[i]);
      if (ret != OK)
      { 
        print_char_error("invalid option -- ", arg[i]);
        break;
      }
    }
  }
  else {
    ret = add_new_data(paths, arg, NULL);
  }
  return (ret);
}

static int  parse_option(t_options *opt, char arg)
{
  int ret = MAJOR_KO;

  for (int i = 0; i < OPTIONS_NUMBER; ++i)
  {
    if (arg == opt->name[i])
    {
      opt->value[i] = true;
      ret = OK;
      break;
    }
  }
  return (ret);
}

bool  get_option(t_options *opt, char arg)
{
  bool  value = false;

  for (int i = 0; i < OPTIONS_NUMBER; ++i)
  {
    if (opt->name[i] == arg)
    {
      value = opt->value[i];
      break;
    }
  }
  return (value);
}
