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

	while (lst)
	{
		t_data *data = (t_data*)lst->content;
		if (data->mode.type == DIREC && not_a_dot(data->name))
		{
			char *path = ft_strdup(data->path);
			if (path == NULL)
			{
				ret = MAJOR_KO;
				break;
			}

			ret = list_path(strat, path);
			if (ret != OK)
			{
				break;
			}
		}
		lst = lst->next;
	}
	return (ret);
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
