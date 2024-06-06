/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:07:03 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 14:07:07 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*no_sorting(t_list* lst, unsigned int lst_len, bool(*sorting)(t_data*, t_data*))
{
	(void)lst;
	(void)lst_len;
	(void)sorting;

	return (lst);
}

bool	sort_by_func(void *a, void *b, bool(*compare)(t_data *data_a, t_data *data_b))
{
	t_data	*data_a = (t_data*)a;
	t_data	*data_b = (t_data*)b;

	return (compare(data_a, data_b));
}

bool	sort_by_name(t_data *a, t_data *b)
{
	return (ls_strcmp(a->file.name, b->file.name) <= 0);
}

bool  sort_by_name_reverse(t_data *a, t_data *b)
{
	return (ls_strcmp(a->file.name, b->file.name) >= 0);
}

bool	sort_by_time(t_data *a, t_data *b)
{
	return (a->time >= b->time);
}

bool	sort_by_time_reverse(t_data *a, t_data *b)
{
	return (a->time <= b->time);
}
