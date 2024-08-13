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

static t_id					*get_new_id(unsigned int key, char *value, unsigned int len);
static inline t_id			*get_id_from_list_by_key(t_list *lst, unsigned int key);
static inline unsigned int	get_hash(unsigned int key);
static void					del_ids(void *ids);

int insert_key(t_list *dict[HASH_SIZE], unsigned int key, char *value, unsigned int len)
{
	unsigned int	hash = get_hash(key);
	t_id			*new_id = get_new_id(key, value, len);
	
	if (new_id == NULL)
	{
		return (INTERNAL_KO);
	}
	
	t_list *new_lst = ft_lstnew(new_id);
	if (new_lst == NULL)
	{
		free(new_id);
		return (INTERNAL_KO);
	}
	ft_lstadd_front(&dict[hash], new_lst);

	return (OK);
}

static t_id	*get_new_id(unsigned int key, char *value, unsigned int len)
{
	t_id	*new_id = ft_malloc(sizeof(t_id));

	if (new_id != NULL)
	{
		new_id->id = key;
		new_id->len = len;
		new_id->value = value;
	}

	return (new_id);
}

t_id *get_id_by_key(t_list * dict[HASH_SIZE], unsigned int key)
{
	unsigned int	hash = get_hash(key);
	t_list			*lst = dict[hash];
	t_id			*id = get_id_from_list_by_key(lst, key);

	return (id);
}

static inline t_id	*get_id_from_list_by_key(t_list *lst, unsigned int key)
{
	t_id	*id = NULL;

	while (lst)
	{
		t_id  *tmp_id = (t_id*)lst->content;
		if (tmp_id->id == key)
		{
			id = tmp_id;
			break;
		}
		lst = lst->next;
	}

	return (id);
}

static inline unsigned int  get_hash(unsigned int key)
{
	return ((unsigned int)(HASH_A * key) >> HASH_SHIFT);
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
