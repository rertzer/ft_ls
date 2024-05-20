/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:50:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 15:51:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_type(t_data *data);
static int	get_type(mode_t	mode);
static int	add_xattr(t_data *data);
static int	set_symlink_type(t_data *data);

int	add_all_stats(t_strategies *strat, t_list *all_paths)
{
	int		ret = OK;
	t_data	*data = NULL;

	while (all_paths != NULL)
	{
		data = (t_data*)all_paths->content;

		ret = add_stats(strat, data);
		if (ret != OK)
		{
			break;
		}
		
		ret = compute_stats(strat, data);
		if (ret != OK)
		{
			break;
		}
		
		if (data->file.type == LNK)
		{
			ret = add_symlink(data);
		}
		
		all_paths = all_paths->next;
	}

	return (ret);
}

int add_stats(t_strategies *strat, t_data *data)
{
	int			ret = OK;
	struct stat	stat_buffer;
		
	errno = 0;
	if (lstat(data->path, &stat_buffer) != 0)
	{
		ret = MAJOR_KO;
		ft_putstr_fd("ft_ls: lstat: ", 2);
		perror(data->path);
	}
	else
	{
		data->dev = stat_buffer.st_dev;
		data->rdev = stat_buffer.st_rdev;
		data->links = stat_buffer.st_nlink;
		data->file.mode = stat_buffer.st_mode;
		data->uid = stat_buffer.st_uid;
		data->gid = stat_buffer.st_gid;
		data->total_size = stat_buffer.st_size;
		data->block_size = stat_buffer.st_blksize;
		data->block_nb = stat_buffer.st_blocks;
		data->time = strat->setTime(&stat_buffer);
	}
	ret = add_xattr(data);

	return (ret);
}

static int  add_xattr(t_data *data)
{
	int	ret = OK;

	errno = 0;
	ssize_t	xattr_nb = listxattr(data->path, NULL, 0);
	if (xattr_nb < 0)
	{
		ret = xattr_error(data);	
	}
	else if (xattr_nb == 16 || xattr_nb == 0)
	{
		data->xattr = false;
	}
	else
	{
		data->xattr = true;
	}

	return (ret); 
}

int  compute_stats(t_strategies *strat, t_data *data)
{
	(void)strat;
	return(set_type(data));
}

static int set_type(t_data *data)
{
	int	ret = OK;

	data->file.type = get_type(data->file.mode);

	if (data->file.type == ERROR_TYPE)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(data->file.name, 2);
		ft_putstr_fd(": invalid file type\n", 2);
		ret = MAJOR_KO;
	}
	return (ret); 
}

static int	get_type(mode_t	mode)
{
	mode_t const modes[] = {S_IFREG, S_IFDIR, S_IFCHR, S_IFBLK, S_IFIFO, S_IFLNK, S_IFSOCK};
	mode &= S_IFMT;

	for (int i = 0; i < MODES_NB; ++i)
	{
		if(mode == modes[i])
		{
			return (i);
		}
	}
	
	return (ERROR_TYPE);
}

int	add_symlink(t_data *data)
{
	int	ret = OK;
	
	data->target.name = ft_malloc(sizeof(char) * (data->total_size + 1));
	if (data->target.name == NULL)
	{
		return (INTERNAL_KO);
	}

	errno = 0;
	ssize_t	size = readlink(data->path, data->target.name, data->total_size);
	if (size < 0 || size != (ssize_t)data->total_size)
	{
		perror("ft_ls: readlink: ");
		return (MAJOR_KO);
	}

	data->target.name[data->total_size] = '\0';
	ret = set_symlink_type(data);

	return (ret);
}

static int	set_symlink_type(t_data *data)
{
	int			ret = OK;
	struct stat	stat_buffer;
    
	errno = 0;
	if (stat(data->path, &stat_buffer) != 0)
	{
		if (errno == ENOENT)
		{
			data->target.type = ERROR_TYPE;
			data->file.broken = true;
		}
		else
		{
			ret = MAJOR_KO;
			ft_putstr_fd("ft_ls: stat: ", 2);
			perror(data->path);
		}
	}
	else 
	{
    	data->target.type = get_type(stat_buffer.st_mode);
		data->target.mode = stat_buffer.st_mode;
		if (data->target.type == ERROR_TYPE)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(data->file.name, 2);
			ft_putstr_fd(": invalid file type\n", 2);
			ret = MAJOR_KO;
		}
	}
	return (ret);
}
