/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathlisting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:17:53 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 15:17:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


static void			sort_apart_files_and_dirs(t_strategies *strat, t_list **all_paths, t_directory *reg_files);
static void			move_to_reg_files(t_directory *reg_files, t_list **files_prev, t_list **all_paths, t_list *path_prev, t_list *current);
static inline void	add_to_reg_files(t_directory *reg_files, t_list **files_prev, t_list *current);
static inline void	remove_from_all_paths(t_list **all_paths, t_list *path_prev, t_list *current);
static inline void	reset_next(t_list **next,t_list *current);
static inline void	next_path(t_list **path_prev, t_list **next, t_list *current);
static int			list_all_files(t_strategies *strat, t_list **all_paths);
static int			handle_reg_files(t_strategies *strat, t_directory *reg_files);

int	process_all_paths(t_strategies *strat, t_list **all_paths, unsigned int len)
{
	int	ret = OK;
	int	status = ret;

	sort_paths(strat, all_paths, len);
	ret = add_all_stats(strat, *all_paths);
	status = major_status(ret);
	if (ret != INTERNAL_KO)
	{
		ret = list_all_files(strat, all_paths);
		if (ret != INTERNAL_KO)
		{
			ret = list_all_path(strat, *all_paths);
		}
		status = worst(status, ret);
	}

	return (status);
}

void sort_paths(t_strategies *strat, t_list **all_paths, unsigned int len)
{
	*all_paths = strat->sortingalgo(*all_paths, len, strat->sorting);
	*all_paths = strat->sortingalgo(*all_paths, len, strat->othersorting);
}

static int	list_all_files(t_strategies *strat, t_list **all_paths)
{
	int			ret = OK;
	t_directory	reg_files;
	init_dir(&reg_files);
	sort_apart_files_and_dirs(strat, all_paths, &reg_files);
	ret = handle_reg_files(strat, &reg_files);
	return (ret);
}

static void	sort_apart_files_and_dirs(t_strategies *strat, t_list **all_paths, t_directory *reg_files)
{
	t_list		*files_prev = NULL;
	t_list		*path_prev = NULL;
	t_list		*next = NULL;

	for (t_list *current = *all_paths; current != NULL; current = next)
	{
		t_data* data = (t_data*)current->content;
		if (data->file.mode == UINT_MAX)
		{
			remove_from_all_paths(all_paths, path_prev, current);
			reset_next(&next, current);
			ft_lstdelone(current, data_del);
		}
		else if (! strat->isdirectory(data))
		{
			move_to_reg_files(reg_files, &files_prev, all_paths, path_prev, current);	
			reset_next(&next, current);
		}
		else
		{
			next_path(&path_prev, &next, current);
		}
	}
}

static void	move_to_reg_files(t_directory *reg_files, t_list **files_prev, t_list **all_paths, t_list *path_prev, t_list *current)
{
	add_to_reg_files(reg_files, files_prev, current);
	remove_from_all_paths(all_paths, path_prev, current);
	++(reg_files->entry_nb);
}

static inline void	add_to_reg_files(t_directory *reg_files, t_list **files_prev, t_list *current)
{

	if (*files_prev == NULL)
	{
		reg_files->content = current;
	}
	else
	{
		(*files_prev)->next = current;
	}
	*files_prev = current;
}

static inline void	remove_from_all_paths(t_list **all_paths, t_list *path_prev, t_list *current)
{
	if (path_prev == NULL)
	{
		*all_paths = current->next;
	}
	else
	{
		path_prev->next = current->next;
	}
}

static inline void	reset_next(t_list **next, t_list *current)
{
	*next = current->next;
	current->next = NULL;
}

static inline void	next_path(t_list **path_prev, t_list **next, t_list *current)
{
	*path_prev = current;
	*next = current->next;
}

static int	handle_reg_files(t_strategies *strat, t_directory *reg_files)
{
	int	ret = OK;

	sort_paths(strat, &reg_files->content, reg_files->entry_nb);
	//reg_files->content = strat->sortingalgo(reg_files->content, reg_files->entry_nb, strat->sorting);
	//reg_files->content = strat->sortingalgo(reg_files->content, reg_files->entry_nb, strat->othersorting);
	if (reg_files->content != NULL)
	{
		ret = format(strat, reg_files);
		free_directory(reg_files);
	}
	return (ret);
}

int	list_all_path(t_strategies *strat, t_list *all_paths)
{
	int		ret = OK;
	int		status = ret;

	while (all_paths != NULL)
	{
		t_data	*data = (t_data*)all_paths->content;
		
		ret = list_path(strat, data->path);

		if (ret == INTERNAL_KO)
		{
			status = ret;
			break;
		}
		status = ret > status ? ret : status;
		all_paths = all_paths->next;
	}

	return (status);
}

int	default_path(t_strategies *strat)
{
	return (list_path(strat, "."));
}
