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

static char	*getpw_username(uid_t id);
static char	*getgr_groupname(gid_t id);

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

char *get_user_name(t_strategies *strat, uid_t id)
{
	char	*name = get_value_by_key(strat->users, id);

	if (name == NULL)
	{
		name = getpw_username(id);
		if (name != NULL)
		{
			insert_key(strat->users, id, name);
		}
	}

	return (name);
}

char *get_group_name(t_strategies *strat, gid_t id)
{
	char	*name = get_value_by_key(strat->groups, id);

	if (name == NULL)
	{
		name = getgr_groupname(id);
		if (name != NULL)
		{
			insert_key(strat->groups, id, name);
		}
	}

	return (name);
}

static char  *getpw_username(uid_t id)
{
	char	*name = NULL;

	errno = 0;
	struct passwd	*psw = getpwuid(id);
	if (psw == NULL)
	{
		if (errno != 0)
		{
			perror("ft_ls: getpwuid: ");
		}
	}
	else
	{
		name = ft_strdup(psw->pw_name);
	}

	return (name);
}

static char  *getgr_groupname(gid_t id)
{
	char	*name = NULL;

	errno = 0;
	struct group *grp = getgrgid(id);
	if (grp == NULL)
	{
		if (errno != 0)
		{
			perror("ft_ls: getgrgid: ");
		}
	}
	else
	{
		name = ft_strdup(grp->gr_name);
	}

	return (name);
}
