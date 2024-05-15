/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:44:08 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 11:44:14 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	int           ret = OK;
	t_options     opt;
	t_list        *all_paths = NULL;
	t_strategies  strat;

	//read args: set options
	ret = parse_all_args(&opt, &all_paths, argc, argv);
	if (ret != OK)
		return (ret);

	ret = set_strategies(&opt, &strat);
	if (ret != OK)
	{
		ft_lstclear(&all_paths, data_del);
		return (ret);
	}
	init_ids(&strat);

	int	path_nb = ft_lstsize(all_paths);

	if (path_nb == 0)
	{
		strat.print_path_name = false;
		ret = default_path(&strat);
	}
	else
	{
		if (path_nb == 1)
		{
			strat.print_path_name = false;
		}

		ret = add_all_stats(&strat, all_paths);
		if (ret == OK)
		{
			bubble_sort(all_paths, strat.sorting);
			bubble_sort(all_paths, strat.othersorting);
			ret = list_all_files(&strat, &all_paths);
			if (ret == OK)
			ret = list_all_path(&strat, all_paths);
		}
	}

	ft_lstclear(&all_paths, data_del);
	free_ids(&strat);
	return (ret);
}
