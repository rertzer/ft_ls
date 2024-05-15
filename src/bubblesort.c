/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:30:23 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 13:30:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	swap(t_list *current);

int bubble_sort(t_list *lst, bool(*ordered)(t_data *a, t_data *b))
{
	bool    sorted = false;
	t_list  *current = lst;

	if (ordered == NULL)
	{
		return (OK);
	}
	while (sorted == false)
	{
		sorted = true;
		current = lst;
		while(current)
		{
			if (current->next && ! sort_by_func(current->content, current->next->content, ordered))
			{
				swap(current);
				sorted = false;
			}
			current = current->next;
		}
	}
	return (OK);
}

static inline void	swap(t_list *current)
{
	void    *tmp = NULL;

	tmp = current->content;
	current->content = current->next->content;
	current->next->content = tmp;
}
