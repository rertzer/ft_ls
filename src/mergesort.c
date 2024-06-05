/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:58:51 by rertzer           #+#    #+#             */
/*   Updated: 2024/06/05 08:58:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list 			*merge(t_list *l_lst, t_list *r_lst, unsigned int l_len, unsigned int r_len, bool(*ordered)(t_data *a, t_data *b));
static inline t_list	*append_remaining(t_list **dest, t_list *src, unsigned int src_len);


t_list *merge_sort(t_list *lst, unsigned int len, bool(*ordered)(t_data *a, t_data *b))
{
	if (len < 2 || ordered == NULL)
	{
		return lst;
	}
	unsigned int	l_len = len / 2;
	unsigned int	r_len = len - l_len;

	t_list	*l_lst = lst;
	t_list	*r_lst = lst;
	for (unsigned int i = 0; i < l_len; ++i)
	{
		r_lst = r_lst->next;
	}
	
	l_lst = merge_sort(l_lst, l_len, ordered);
	r_lst = merge_sort(r_lst, r_len, ordered);

	return merge(l_lst, r_lst, l_len, r_len, ordered);
}

static t_list *merge(t_list *l_lst, t_list *r_lst, unsigned int l_len, unsigned int r_len, bool(*ordered)(t_data *a, t_data *b))
{
	t_list	*merged = NULL;
	t_list	*current = NULL;
	t_list	*next	= NULL;

	while (l_len && r_len)
	{
		if (sort_by_func(l_lst->content, r_lst->content, ordered))
		{
			next = l_lst;
			l_lst = l_lst->next;
			--l_len;
		}
		else
		{
			next = r_lst;
			r_lst = r_lst->next;
			--r_len;
		}
		if (merged == NULL)
		{
			merged = next;
		}
		else
		{
			current->next = next;
		}
		current = next;
	}
	current = append_remaining(&current, l_lst, l_len);
	current = append_remaining(&current, r_lst, r_len);
	
	return (merged);
}

static inline t_list	*append_remaining(t_list **dest, t_list *src, unsigned int src_len)
{
	t_list *current = *dest;

	while (src_len)
	{
		if (current == NULL)
		{
			*dest = src;
		}
		else
		{
			current->next = src;
		}
		current = current->next;
		src = src->next;
		--src_len;
	}
	current->next = NULL;
	return (current);
}
