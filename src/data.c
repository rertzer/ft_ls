/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:43:53 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 09:44:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static  int			add_data_path(t_data *data, char const * const name, char const * const path);

t_data	*add_new_data(t_list **lst, char const * const name, char const * const path, void (*lstadd)(t_list**, t_list*))
{
	t_data  *data = NULL;
	t_list  *newlst = NULL;

	if ((data = new_data()) == NULL || \
		(data->file.name = ft_pathdup(name)) == NULL || \
		(add_data_path(data, data->file.name, path)) != OK || \
		(newlst = ft_lstnew(data)) == NULL)
	{
		data_del(data);
		data = NULL;
	}
	else
	{
		lstadd(lst, newlst);
	}
	return (data);
}

static  int add_data_path(t_data *data, char const * const name, char const * const path)
{
	int ret = OK;
	if (path == NULL)
	{
		data->path = ft_longdup(name);
	}
	else
	{
		data->path = ft_pathjoin(path, data->file.name);
	}
	if (data->path == NULL)
	{
		ret = INTERNAL_KO;
	}
	return (ret);
}

t_data  *new_data()
{
	t_data *data = ft_malloc(sizeof(t_data));
	if (data != NULL)
	{
		data->file.name = NULL;
		data->path = NULL;
		data->target.name = NULL;
		data->target.type = -1;
		data->target.mode = -1;
		data->file.broken = false;
		data->target.broken = false;
	}
	return (data);
}

void  data_del(void *v_data)
{
	if (v_data != NULL)
	{
		t_data  *data = (t_data*)v_data;
		free(data->file.name);
		free(data->path);
		free(data->target.name);
		free(data);
	}
}

bool	is_directory_simple(t_data *data)
{
	int	ret = false;
	
	if(data->file.type == DIREC || (data->file.type == LNK && data->target.type == DIREC))
	{
		ret = true;
	}
	return (ret);
}

bool	is_directory_longlist(t_data *data)
{
	int	ret = false;

	if(data->file.type == DIREC)
	{
		ret = true;
	}
	return (ret);

}

bool	is_directory_nodir(t_data *data)
{
	(void)data;

	return (false);
}
