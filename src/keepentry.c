/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keepentry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:52:32 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 10:52:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool  keep_all(const struct dirent* const entry)
{
	(void)entry;

	return (true);
}

bool  skip_dot(const struct dirent* const entry)
{
	bool	ret = true;

	if (entry->d_name[0] == '.')
	{
		ret = false;
	}

	return (ret);
}
