/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:27 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/13 18:07:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool  recent_year(char *time_string, char *now_string, int year_offset);
static bool  recent_six_month_ago(char *time_string, char *now_string);
static int  getMonth(char *time);
static int  getYear(char *time);
static int getDay(char *time);

bool recent(char *time_string)
{
  bool recent = false;
  errno = 0;
  time_t now = time(NULL);
  if (now == -1)
  {
    perror("ft_ls: time: ");
    return (0);
  }
  char  *now_string = ctime(&now);
  if (now_string == NULL)
  {
    perror("ft_ls: ctime: ");
    return (0);
  }
   int time_year = getYear(&time_string[20]);
   int now_year = getYear(&now_string[20]);
   recent = recent_year(time_string, now_string, now_year - time_year);
 
  return recent;
}

static  bool  recent_year(char *time_string, char *now_string, int year_offset)
{
  bool  recent = false;
  int time_month = getMonth(&time_string[4]);
  int now_month = getMonth(&now_string[4]);

  int month_ago = now_month - time_month + 12 * year_offset;
  if (month_ago < 6)
      recent = true;
  else if (month_ago == 6){
    recent = recent_six_month_ago(time_string, now_string);
  }
  return (recent);
}

static  bool  recent_six_month_ago(char *time_string, char *now_string)
{
  bool  recent = false;
  int time_day = getDay(&time_string[4]);
  int now_day = getDay(&now_string[4]);

  if (time_day >= now_day)
  {
      recent = true;
  }
  return (recent);
}

static int  getMonth(char *time)
{
  char  *month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  
  for (int i = 0; i < 12; ++i)
  {
    if (ft_strncmp(time, month[i], 3) == 0)
      return (i);
  }
  return (-1);
}

static  int getYear(char *time)
{
  return ft_atoi(time);
}

static  int getDay(char *time)
{
  return ft_atoi(time);
}


