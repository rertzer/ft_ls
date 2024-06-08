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

static int	return_reformat(int ret);

int main(int argc, char **argv)
{
	int           ret = OK;
	t_options     opt;
	t_list        *all_paths = NULL;
	t_strategies  strat;

	ret = parse_all_args(&opt, &all_paths, argc, argv);
	if (ret != OK)
	{
		ft_lstclear(&all_paths, data_del);
		return (return_reformat(ret));
	}

	ret = set_strategies(&opt, &strat);
	if (ret != OK)
	{
		ft_lstclear(&all_paths, data_del);
		return (return_reformat(ret));
	}

	init_ids(&strat);
	int	path_nb = ft_lstsize(all_paths);

	if (path_nb < 2 && get_option(&opt, 'R') == false)
	{
		strat.print_path_name = false;
	}
	if (path_nb == 0)
	{
		ret = default_path(&strat);
	}
	else
	{
		ret = process_all_paths(&strat, &all_paths, path_nb);
	}

	ft_lstclear(&all_paths, data_del);
	free_ids(&strat);
	return (return_reformat(ret));
}

static int	return_reformat(int ret)
{
	if (ret == INTERNAL_KO)
	{
		ret = MAJOR_KO;
	}
	return (ret);
}
