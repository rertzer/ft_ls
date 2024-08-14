/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:13:18 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/14 14:13:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list_copied_path(t_strategies *strat, char *path);

int	list_path(t_strategies *strat, char* path)
{
	int	ret = OK;

	char	*dup_path = ft_longdup(path);
	if (dup_path == NULL)
	{
		ret = INTERNAL_KO;
	}
	else
	{
		ret = list_copied_path(strat, dup_path);
	}

	return (ret);
}

static int	list_copied_path(t_strategies *strat, char *path)
{
	int			ret = OK;
	int			status = ret;
	t_directory	dir;

	init_dir(&dir);
	dir.path = path;
	ret = get_dir_content(strat, &dir);
	status = worst(status, ret);
	
	if (ret != INTERNAL_KO)
	{
		sort_paths(strat, &dir.content, dir.entry_nb);
		ret = format(strat, &dir);
		status = ret > status ? ret : status;
		if (ret != INTERNAL_KO)
		{
			ret = strat->recurse(strat, &dir);
			status = ret > status ? ret : status;
		}
	}

	free_directory(&dir);

	return (status);
}
