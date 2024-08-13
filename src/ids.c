/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:14:42 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 13:14:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	add_user_name(t_strategies *strat, char **name, unsigned int *len, uid_t id);
static int	add_group_name(t_strategies *strat, char **name, unsigned int *len, gid_t id);
static int	getpw_username(uid_t id, char **name);
static int	get_passwd_struct(uid_t id, struct passwd **psw);
static int	getgr_groupname(gid_t id, char **name);
static int	get_group_struct(gid_t id, struct group **grp);

void  init_ids(t_strategies *strat)
{
	init_dict(strat->users);
	init_dict(strat->groups);
}

void  free_ids(t_strategies *strat)
{
	free_dict(strat->users);
	free_dict(strat->groups);
}

int	get_user_name(t_strategies *strat, char **name, unsigned int *len, uid_t id)
{
	int	ret = OK;
	t_id *uid = get_id_by_key(strat->users, id);

	if (uid != NULL)
	{
		*name = uid->value;
		*len = uid->len;
	}
	else
	{
		*name = NULL;
		*len = 0;
		ret = add_user_name(strat, name, len, id);
	}

	return (ret);
}

static int	add_user_name(t_strategies *strat, char **name, unsigned int *len, uid_t id)
{
	int	ret = getpw_username(id, name);
	if (*name != NULL)
	{
		*len = ft_strlen(*name);
		if (insert_key(strat->users, id, *name, *len) == INTERNAL_KO)
		{
			free(*name);
			*name = NULL;
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}

int	get_group_name(t_strategies *strat, char **name, unsigned int *len, gid_t id)
{
	int	ret = OK;

	t_id *gid = get_id_by_key(strat->groups, id);

	if (gid != NULL)
	{
		*name = gid->value;
		*len = gid->len;
	}
	else
	{
		*name = NULL;
		*len = 0;
		ret = add_group_name(strat, name, len, id);		
	}

	return (ret);
}

static int	add_group_name(t_strategies *strat, char **name, unsigned int *len, gid_t id)
{
	int	ret = getgr_groupname(id, name);
	
	if (*name != NULL)
	{
		*len = ft_strlen(*name);
		if (insert_key(strat->groups, id, *name, *len) == INTERNAL_KO)
		{
			free(*name);
			*name = NULL;
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}

static int	getpw_username(uid_t id, char **name)
{
	int	ret = OK;
	*name = NULL;
	struct passwd	*psw = NULL;

	ret = get_passwd_struct(id,  &psw);
	if (psw != NULL)
	{
		*name = ft_longdup(psw->pw_name);
		if (*name == NULL)
		{
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}

static int	get_passwd_struct(uid_t id, struct passwd **psw)
{
	int	ret = OK;
	errno = 0;

	*psw = getpwuid(id);
	
	if (*psw == NULL && errno != 0)
	{
		perror("ft_ls: getpwuid: ");
		ret = MINOR_KO;
	}
	
	return (ret);
}

static int	getgr_groupname(gid_t id, char **name)
{
	int		ret = OK;
	*name = NULL;
	struct group *grp = NULL;

	ret = get_group_struct(id, &grp);
	if (grp != NULL)
	{
		*name = ft_longdup(grp->gr_name);
		if (*name == NULL)
		{
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}

static int	get_group_struct(gid_t id, struct group **grp)
{
	int	ret = OK;
	errno = 0;

	*grp = getgrgid(id);

	if (*grp == NULL && errno != 0)
	{
		perror("ft_ls: getgrgid: ");
		ret = MINOR_KO;
	}

	return (ret);
}
