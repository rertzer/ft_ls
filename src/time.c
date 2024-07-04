/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:17:59 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/07 16:18:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct timespec  last_modif(struct stat *stat_buffer)
{
  return (stat_buffer->st_mtim);
}

struct timespec  access_time(struct stat *stat_buffer)
{
  return (stat_buffer->st_atim);
}

char	*get_time_string(time_t *time)
{
	errno = 0;
	
	char  *tmp = ctime(time);
	if (tmp == NULL)
	{
		perror("ft_ls: ctime: ");
		return (NULL);
	}

//	char  *time_string = ft_longdup(tmp);

//	return (time_string);
	return (tmp);
}
