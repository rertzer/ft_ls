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
	struct dirent	*dir_entry = NULL;
	
	errno = 0;
	DIR	*dir_stream = opendir(dir->path);
	if (dir_stream == NULL)
	{
		ft_putstr_fd("ls: cannot open directory '", 2);
		ft_putstr_fd(dir->path, 2);
		perror("'");
		ret = MINOR_KO;
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
				if (ret == INTERNAL_KO)
				{
					break;
				}
			}
		}
		if (errno != 0 && ret == OK)
		{
			ret = MAJOR_KO;
			ft_putstr_fd("ls: cannot read directory '", 2);
			ft_putstr_fd(dir->path, 2);
			perror("'");
		}
	}
	closedir(dir_stream);
	return (ret);
}
     
static int add_entry(t_strategies *strat, t_directory *dir, struct dirent *dir_entry)
{
	int	ret = OK;

	ret = add_new_data(&dir->content, dir_entry->d_name, dir->path);
	if (ret != OK)
	{
		return (ret);
	}

	++dir->entry_nb;

	ret = add_stats(strat, (t_data*)dir->content->content);
	if (ret != OK)
	{
		return (ret);
	}

	ret = compute_stats(strat, (t_data*)dir->content->content);

	if (ret == OK && ((t_data*)dir->content->content)->type == LNK)
	{
		ret = add_symlink((t_data*)dir->content->content);
	}

	return (ret);
}
