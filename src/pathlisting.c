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


static inline void	add_to_reg_files(t_directory *reg_files, t_list **files_prev, t_list *current);
static inline void	remove_from_all_paths(t_list **all_paths, t_list *path_prev, t_list *current);
static inline void	reset_next(t_list **next,t_list *current);
static inline void	next_path(t_list **path_prev, t_list **next, t_list *current);
static int			handle_reg_files(t_strategies *strat, t_directory *reg_files);
static int			list_duplicated_path(t_strategies *strat, char *path);

int	process_all_paths(t_strategies *strat, t_list **all_paths, unsigned int len)
{
	
	int	ret = OK;
	int	status = ret;
	ret = add_all_stats(strat, *all_paths);
	if (ret == MINOR_KO)
	{
		ret = MAJOR_KO;
	}
	status = ret;
	if (ret != INTERNAL_KO)
	{
		*all_paths = strat->sortingalgo(*all_paths, len, strat->sorting);
		*all_paths = strat->sortingalgo(*all_paths, len, strat->othersorting);
		ret = list_all_files(strat, all_paths);
		if (ret == OK)
		{
			ret = list_all_path(strat, *all_paths);
		}
		status = ret > status ? ret : status;
	}

	return (status);
}

int	list_all_files(t_strategies *strat, t_list **all_paths)
{
	
	int			ret = OK;
	t_directory	reg_files;
	t_list		*current = *all_paths;
	t_list		*files_prev = NULL;
	t_list		*path_prev = NULL;
	t_list		*next = NULL;

	init_dir(&reg_files);

	while (current != NULL)
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
			add_to_reg_files(&reg_files, &files_prev, current);
			remove_from_all_paths(all_paths, path_prev, current);
			reset_next(&next, current);
			++reg_files.entry_nb;
		}
		else
		{
			next_path(&path_prev, &next, current);
		}
		current = next;
	}
	ret = handle_reg_files(strat, &reg_files);
	return (ret);
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

	reg_files->content = strat->sortingalgo(reg_files->content, reg_files->entry_nb, strat->sorting);
	reg_files->content = strat->sortingalgo(reg_files->content, reg_files->entry_nb, strat->othersorting);
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
		ret = list_duplicated_path(strat, dup_path);
	}

	return (ret);
}

static int	list_duplicated_path(t_strategies *strat, char *path)
{
	int			ret = OK;
	int			status = ret;
	t_directory	dir;

	init_dir(&dir);
	dir.path = path;
	ret = get_dir_content(strat, &dir);
	status = ret > status ? ret : status;
	
	if (ret != INTERNAL_KO)
	{
		dir.content = strat->sortingalgo(dir.content, dir.entry_nb, strat->sorting);
		dir.content = strat->sortingalgo(dir.content, dir.entry_nb, strat->othersorting);
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
