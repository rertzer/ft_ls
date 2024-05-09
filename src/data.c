/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:43:53 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 09:44:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static  int add_data_path(t_data *data, char const * const name, char const * const path);

int add_new_data(t_list **lst, char const * const name, char const * const path)
{
  int     ret = OK;
  t_data  *data = NULL;
  t_list  *newlst = NULL;

  if (  (data = new_data()) == NULL || \
        (data->name = ft_strdup(name)) == NULL || \
        (add_data_path(data, name, path)) != OK || \
        (newlst = ft_lstnew(data)) == NULL)
  {
    data_del(data);
    ret = MAJOR_KO;
  }
  else {
    ft_lstadd_front(lst, newlst);
  }
  return (ret);
}

static  int add_data_path(t_data *data, char const * const name, char const * const path)
{
  int ret = OK;
  if (path == NULL){
    data->path = ft_strdup(name);
  }
  else {
    data->path = ft_pathjoin(path, data->name);
  }
  if (data->path == NULL)
  {
    ret = MAJOR_KO;
  }
  return (ret);
}

t_data  *new_data()
{
  errno = 0;
  t_data *data = malloc(sizeof(t_data));
  if (data != NULL)
  {
    data->name = NULL;
    data->path = NULL;
  }
  else {
    perror("ft_ls: malloc: ");
  }
  return (data);
}

void  data_del(void *v_data)
{
  if (v_data != NULL)
  {
    t_data  *data = (t_data*)v_data;
    free(data->name);
    free(data->path);
    free(data);
  }
}
