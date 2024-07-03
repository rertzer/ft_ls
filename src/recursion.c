/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:22:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 14:22:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool	not_a_dot(char *name);

int	no_recursion(t_strategies *strat, t_directory *dir)
{
	(void)strat;
	(void)dir;
	return (OK);
}

int	recursive(t_strategies *strat, t_directory *dir)
{
	t_list	*lst = dir->content;
	int		ret = OK;
	int		status = OK;

	while (lst)
	{
		t_data *data = (t_data*)lst->content;
		if (data->file.type == DIREC && not_a_dot(data->file.name))
		{
			ret = list_path(strat, data->path);
			if (ret == INTERNAL_KO)
			{
				status = ret;
				break;
			}
		}
		lst = lst->next;
		status = ret > status ? ret : status;
	}
	return (status);
}

static bool not_a_dot(char *name)
{
	bool	is_not = true;
	
	if (!(ft_strcmp(name, ".") && ft_strcmp(name, "..")))
	{
		is_not = false;
	}
	
	return (is_not);
}
