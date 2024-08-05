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
static int	load_stats(t_strategies *strat, t_data *data);
static int	add_xattr(t_data *data);

int	add_all_stats(t_strategies *strat, t_list *all_paths)
{
	int		ret = OK;
	int		status = ret;
	t_data	*data = NULL;

	while (all_paths != NULL)
	{
		data = (t_data*)all_paths->content;
		ret = add_stats(strat, data);	
		status = ret > status ? ret : status;
		all_paths = all_paths->next;
	}

	return (status);
}

int	add_stats(t_strategies *strat, t_data *data)
{
	int	ret = OK;

	ret = load_stats(strat, data);

	if (ret == OK)
	{
		ret = compute_stats(strat, data);
		if (ret == OK)
		{
			if (data->file.type == LNK)
			{
				ret = add_symlink(data);
			}
			else
			{
				ret = add_xattr(data);
			}
		}
	}
	return (ret);
}

static int load_stats(t_strategies *strat, t_data *data)
{
	int			ret = OK;
	struct stat	stat_buffer;
		
	errno = 0;
	if (lstat(data->path, &stat_buffer) != 0)
	{
		print_perror_msg("cannot access '", data->path);
		ret = MINOR_KO;
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
		data->time = strat->settime(&stat_buffer);
	}

	return (ret);
}

static int  add_xattr(t_data *data)
{
	int	ret = OK;

	data->xattr = false;
	errno = 0;
	ssize_t	xattr_len = listxattr(data->path, NULL, 0);

	if (xattr_len > 0)
	{
		data->xattr = true;
		char *xattr_str = ft_malloc(sizeof(char) * (xattr_len));
		if (xattr_str == NULL)
		{
			return (INTERNAL_KO);
		}

		ssize_t	xattrlst_len = listxattr(data->path, xattr_str, xattr_len);
		if (xattr_len != xattrlst_len)
		{
			return (MINOR_KO);
		}
		if (xattr_len == 16 && ! ft_strcmp(xattr_str, "system.nfs4_acl"))
		{
			data->xattr = false;
		}
		else if (xattr_len == 28 && ! ft_strcmp(xattr_str, "user.random-seed-creditable"))
		{
			data->xattr = false;
		}
		else if (xattr_len == 20 && ! ft_strcmp(xattr_str, "security.capability"))
		{
			data->xattr = false;
		}
		else if (xattr_len == 24 && ! ft_strcmp(xattr_str, "user.xdg.inactive-since"))
		{
			data->xattr = false;
		}
		free(xattr_str);
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
		ret = MINOR_KO;
	}
	return (ret); 
}

int	get_type(mode_t	mode)
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
