/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dircontent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:50:14 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 15:50:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int add_entry(t_strategies *strat, t_directory *dir, struct dirent *dir_entry);

int get_dir_content(t_strategies *strat, t_directory *dir)
{
	int				ret = OK;
	int				status = ret;
	struct dirent	*dir_entry = NULL;
	
	errno = 0;
	DIR	*dir_stream = opendir(dir->path);
	if (dir_stream == NULL)
	{
		print_perror_msg("cannot open directory '", dir->path);
		dir->valid = false;
		status = MINOR_KO;
	}
	else
	{
		while (true)
		{
			errno = 0;
			dir_entry = readdir(dir_stream);
			if (dir_entry == NULL)
				break;
			if (strat->keepEntry(dir_entry))
			{
				ret = add_entry(strat, dir, dir_entry);
				status = status > ret ? status : ret;
				if (ret == INTERNAL_KO)
				{
					break;
				}
			}
		}
		if (errno != 0 && ret == OK)
		{
			status = print_perror_msg("cannot read directory '", dir->path);
			dir->valid = false;
		}
	}
	closedir(dir_stream);

	return (status);
}
     
static int add_entry(t_strategies *strat, t_directory *dir, struct dirent *dir_entry)
{
	int	ret = OK;

	t_data*	data = add_new_data(&dir->content, dir_entry->d_name, dir_entry->d_type,dir->path, strat->addlist);

	if (data == NULL)
	{
		ret = INTERNAL_KO;
	}
	else
	{
		++dir->entry_nb;
		ret = add_stats(strat, data);
	}

	return (ret);
}
