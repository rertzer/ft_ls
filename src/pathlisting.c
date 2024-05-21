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
static void			handle_reg_files(t_strategies *strat, t_directory *reg_files);

int	process_all_paths(t_strategies *strat, t_list **all_paths)
{
	int	ret = OK;

	ret = add_all_stats(strat, *all_paths);
	if (ret == OK)
	{
		strat->sortingalgo(*all_paths, strat->sorting);
		bubble_sort(*all_paths, strat->othersorting);
		ret = list_all_files(strat, all_paths);
		if (ret == OK)
		{
			ret = list_all_path(strat, *all_paths);
		}
	}

	return (ret);
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
		if (! strat->isdirectory(data))
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
	handle_reg_files(strat, &reg_files);
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

static void	handle_reg_files(t_strategies *strat, t_directory *reg_files)
{
	if (reg_files->content != NULL)
	{
		format(strat, reg_files);
		free_directory(reg_files);
	}
}

int	list_all_path(t_strategies *strat, t_list *all_paths)
{
	int		ret = OK;
	char	*path = NULL;

	while (all_paths != NULL)
	{
		t_data	*data = (t_data*)all_paths->content;
		
		path = ft_strdup(data->path);
		if (path == NULL)
		{
			ret = INTERNAL_KO;
			break;
		}

		ret = list_path(strat, path);
		if (ret != OK)
		{
			break;
		}

		all_paths = all_paths->next;
	}

	return (ret);
}

int	default_path(t_strategies *strat)
{
	int	ret = OK;

	char	*path = strdup(".");
	if (path == NULL)
	{
		ret = INTERNAL_KO;
	}
	else
	{
		ret = list_path(strat, path);
	}

	return (ret);
}

int	list_path(t_strategies *strat, char* path)
{
	int			ret = OK;
	t_directory	dir;

	init_dir(&dir);
	dir.path = path;

	ret = get_dir_content(strat, &dir);
	if (ret == OK)
	{
		strat->sortingalgo(dir.content, strat->sorting);
		strat->sortingalgo(dir.content, strat->othersorting);
		format(strat, &dir);
	}

	ret = strat->recurse(strat, &dir);
	free_directory(&dir);
	
	return (ret);
}
