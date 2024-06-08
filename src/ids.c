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

static int	getpw_username(uid_t id, char **name);
static int	getgr_groupname(gid_t id, char **name);

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

int	get_user_name(t_strategies *strat, char **name, uid_t id)
{
	int	ret = OK;
	*name = get_value_by_key(strat->users, id);

	if (*name == NULL)
	{
		ret = getpw_username(id, name);
		if (*name != NULL)
		{
			if (insert_key(strat->users, id, *name) == INTERNAL_KO)
			{
				free(*name);
				ret = INTERNAL_KO;
			}
		}
	}

	return (ret);
}

int	get_group_name(t_strategies *strat, char **name, gid_t id)
{
	int	ret = OK;

	*name = get_value_by_key(strat->groups, id);

	if (*name == NULL)
	{
		ret = getgr_groupname(id, name);
		if (*name != NULL)
		{
			if (insert_key(strat->groups, id, *name))
			{
				free(*name);
				ret = INTERNAL_KO;
			}
		}
	}

	return (ret);
}

static int	getpw_username(uid_t id, char **name)
{
	int	ret = OK;

	*name = NULL;
	errno = 0;

	struct passwd	*psw = getpwuid(id);
	if (psw == NULL)
	{
		if (errno != 0)
		{
			perror("ft_ls: getpwuid: ");
			ret = MAJOR_KO;
		}
	}
	else
	{
		*name = ft_strdup(psw->pw_name);
		if (*name == NULL)
		{
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}

static int	getgr_groupname(gid_t id, char **name)
{
	int		ret = OK;
	
	*name = NULL;
	errno = 0;

	struct group *grp = getgrgid(id);
	if (grp == NULL)
	{
		if (errno != 0)
		{
			ret = MAJOR_KO;
			perror("ft_ls: getgrgid: ");
		}
	}
	else
	{
		*name = ft_strdup(grp->gr_name);
		if (*name == NULL)
		{
			ret = INTERNAL_KO;
		}
	}

	return (ret);
}
