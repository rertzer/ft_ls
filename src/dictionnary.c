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

static inline unsigned int	get_hash(unsigned int key);
static void					del_ids(void *ids);

int insert_key(t_list *dict[HASH_SIZE], unsigned int key, char *value)
{
	unsigned int	hash = get_hash(key);
	t_id			*newid = ft_malloc(sizeof(t_id));

	if (newid == NULL)
	{
		return (INTERNAL_KO);
	}

	newid->id = key;
	newid->value = value;

	t_list *newlst = ft_lstnew(newid);
	if (newlst == NULL)
	{
		free(newid);
		return (INTERNAL_KO);
	}
	ft_lstadd_front(&dict[hash], newlst);

	return (OK);
}

char* get_value_by_key(t_list * const dict[HASH_SIZE], unsigned int key)
{
	unsigned int	hash = get_hash(key);
	t_list const	*lst = dict[hash];
	char		 	*value = NULL;

	while (lst)
	{
		t_id  *id = (t_id*)lst->content;
		if (id->id == key)
		{
			value = id->value;
			break;
		}
		lst = lst->next;
	}

	return (value);
}

static inline unsigned int  get_hash(unsigned int key)
{
	unsigned int hash = HASH_A * key;
	return (hash >> HASH_SHIFT);
}

void  init_dict(t_list *dict[HASH_SIZE])
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		dict[i] = NULL;
	}
}

void  free_dict(t_list *dict[HASH_SIZE])
{
	for (int i = 0; i < HASH_SIZE; ++i)
	{
		if (dict[i] != NULL)
		{
			ft_lstclear(&dict[i], del_ids);
		}
	}
}

static void  del_ids(void *ids)
{
	t_id *id = (t_id*)ids;
	free(id->value);
	free(id);
}
