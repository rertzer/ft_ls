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

int add_new_data(t_list **lst, char const * const name, char const * const path)
{
  errno = 0;
  t_data *data = malloc(sizeof(t_data));
  
  if (data == NULL)
    {
      perror("ft_ls: malloc: ");
      return (MAJOR_KO);
    }
  //!!!!!!! path + grand que name
  ft_strcpy(data->name, name);
  if (path == NULL){
    data->path = ft_strdup(name);
  }
  else{
    data->path = ft_pathjoin(path, data->name);
  }
  if (data->path == NULL)
  {
      //free(data->name);
      free(data);
      return (MAJOR_KO);
  }
  t_list *newlst = ft_lstnew(data);
  if (newlst == NULL)
  {
    free(data->path);
    //free(data->name);
    free(data);
    return (MAJOR_KO);
  }
  ft_lstadd_front(lst, newlst);
  return (OK);
}

void  data_del(void * v_data)
{
  t_data* data = (t_data*)v_data;
  if (data != NULL)
  {
    free(data->path);
  }
  free(data);
}
