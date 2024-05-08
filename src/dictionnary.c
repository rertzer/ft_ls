/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:44:30 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 11:44:31 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline unsigned int  get_hash(unsigned int key);

int insert_key(t_list *dict[HASH_SIZE], unsigned int key, char *value)
{
  unsigned int hash = get_hash(key);
  errno = 0;
  t_id  *newid = malloc(sizeof(t_id));
  if (newid == NULL)
  {
    perror("ft_ls: malloc: ");
    return (MAJOR_KO);
  }
  newid->id = key;
  newid->value = value;
  t_list *newlst = ft_lstnew(newid);
  if (newlst == NULL)
  {
    free(newid);
    perror("ft_ls: malloc: ");
    return (MAJOR_KO);
  }
  ft_lstadd_front(&dict[hash], newlst);
  return (OK);
}

char* get_value_by_key(t_list *dict[HASH_SIZE], unsigned int key)
{
  unsigned int hash = get_hash(key);
  t_list *lst = dict[hash];
  char  *value = NULL;

  while (lst)
  {
    if (lst->content->key == key)
    {
      value = lst->content->value;
      break;
    }
    lst = lst->next;
  }
  return value;
}

static inline unsigned int  get_hash(unsigned int key)
{
  unsigned int hash = HASH_A * key;
  return (hash >> HASH_SHIFT);
}
