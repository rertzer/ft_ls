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


int	process_all_paths(t_strategies *strat, t_list **all_paths)
{
	int	ret = OK;

	ret = add_all_stats(strat, *all_paths);
	if (ret == OK)
	{
		bubble_sort(*all_paths, strat->sorting);
		bubble_sort(*all_paths, strat->othersorting);
		ret = list_all_files(strat, all_paths);
		if (ret == OK)
		{
			ret = list_all_path(strat, *all_paths);
		}
	}
	return (ret);
}

int list_all_files(t_strategies *strat, t_list **all_paths)
{
	int ret = OK;
	t_directory reg_files;
	t_list *current = *all_paths;
	t_list *files_prev = NULL;
	t_list *path_prev = NULL;
	t_list  *next = NULL;

	init_dir(&reg_files);

	while (current != NULL)
	{
		t_data* data = (t_data*)current->content;
		if (! strat->isdirectory(data))
		{
			if (files_prev == NULL)
				reg_files.content = current;
			else
			{
				files_prev->next = current;
			}
			files_prev = current;
			if (path_prev == NULL)
			{
				*all_paths = current->next;
			}
			else
			{
				path_prev->next = current->next;
			}
			next = current->next;
			current->next = NULL;
			++reg_files.entry_nb;
		}
		else
		{
			path_prev = current;
			next = current->next;
		}
		current = next;
	}
	if (reg_files.content != NULL)
	{
		strat->format(strat, &reg_files);
		free_directory(&reg_files);
	}
	return (ret);
}

int list_all_path(t_strategies *strat, t_list *all_paths)
{
  int   ret = OK;
  char  *path = NULL;

  while (all_paths != NULL)
  {
    t_data  *data = (t_data*)all_paths->content;
    path = ft_strdup(data->path);
    if (path == NULL)
    {
      ret = MAJOR_KO;
      break;
    }
    ret = list_path(strat, path);
    if (ret != OK)
      break;
    all_paths = all_paths->next;
  }
    return (ret);
}

int  default_path(t_strategies *strat)
{
	int	ret = OK;
	char	*path = strdup(".");

	strat->default_path = true; 
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

int list_path(t_strategies *strat, char* path)
{
	int ret = OK;
	t_directory dir;
	init_dir(&dir);
	dir.path = path;

	ret = get_dir_content(strat, &dir);
	if (ret == OK)
	{
		bubble_sort(dir.content, strat->sorting);
		bubble_sort(dir.content, strat->othersorting);
		strat->format(strat, &dir);
	}
	ret = strat->recurse(strat, &dir);
	free_directory(&dir);
	return (ret);
}
