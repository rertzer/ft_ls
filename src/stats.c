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

static int set_type(t_data *data);
static int	get_type(mode_t	mode);
static int  add_xattr(t_data *data);
static int	set_symlink_type(t_data *data);

int add_all_stats(t_strategies *strat, t_list *all_paths)
{
	int		ret = OK;
	t_data	*data = NULL;

	while (all_paths != NULL)
	{
		data = (t_data*)all_paths->content;
		ret = add_stats(strat, data);
		if (ret != OK)
			break;
		ret = compute_stats(strat, data);
		if (ret != OK)
			break;
		all_paths = all_paths->next;
		if (data->type == LNK)
		{
			ret = add_symlink(data);
		}
		else
		{
			data->target_type = -1;
		}
	}
	return (ret);
}

int add_stats(t_strategies *strat, t_data *data)
{
  int ret = OK;
  struct stat stat_buffer;
    
  errno = 0;
  if (lstat(data->path, &stat_buffer) != 0) {
    ret = MAJOR_KO;
    ft_putstr_fd("ft_ls: lstat: ", 2);
    perror(data->path);
  }
  else {
    data->dev = stat_buffer.st_dev;
    data->rdev = stat_buffer.st_rdev;
    data->links = stat_buffer.st_nlink;
    data->mode = stat_buffer.st_mode;
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
	ssize_t xattr_nb = listxattr(data->path, NULL, 0);
	if (xattr_nb < 0)
	{
		if (errno == ENOENT || errno == ELOOP)
		{
			data->xattr = false;
		}
		else
		{
			ft_putstr_fd("ft_ls: listxattr: ", 2);
			perror(data->path);
			ret = MAJOR_KO;
		}
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
  int ret = OK;
  ret = set_type(data);

  return (ret);
}

static int set_type(t_data *data)
{
	int	ret = OK;

	data->type = get_type(data->mode);

	if (data->type == ERROR_TYPE)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(data->name, 2);
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

int  add_symlink(t_data *data)
{
	int	ret = OK;
	
	errno = 0;
	data->target = malloc(sizeof(char) * (data->total_size + 1));
	if (data->target == NULL)
	{
		perror("ft_ls: malloc: ");
		return (MAJOR_KO);
	}
	ssize_t	size = readlink(data->path, data->target, data->total_size);
	if (size < 0 || size != (ssize_t)data->total_size)
	{
		perror("ft_ls: readlink: ");
		return (MAJOR_KO);
	}
	data->target[data->total_size] = '\0';
	ret = set_symlink_type(data);
	return (ret);
}

static int	set_symlink_type(t_data *data)
{
	int ret = OK;
	struct stat stat_buffer;
    
	errno = 0;
	if (stat(data->path, &stat_buffer) != 0)
	{
		ret = MAJOR_KO;
		ft_putstr_fd("ft_ls: stat: ", 2);
		perror(data->path);
	}
	else 
	{
    	data->target_type = get_type(stat_buffer.st_mode);
		if (data->target_type == ERROR_TYPE)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(data->name, 2);
			ft_putstr_fd(": invalid file type\n", 2);
			ret = MAJOR_KO;
		}
	}
	return (ret);
}
