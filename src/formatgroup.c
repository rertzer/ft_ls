/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatgroup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:45:01 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 13:45:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			format_group_group(t_strategies *strat, char **buffer, unsigned int *len, t_data *data);
static unsigned int format_group_id(char **buffer, t_data *data);

int format_group(t_strategies *strat, t_format_data *format_data, unsigned int *size, t_data *data)
{
	int ret = format_group_group(strat, &format_data->group, size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	if (*size == 0)
	{
		*size = format_group_id(&format_data->group, data);
		if (size == 0)
		{
			return (INTERNAL_KO);
		}
		format_data->align_group_left = false;
	}

	return (ret);
}

static int format_group_group(t_strategies *strat, char **buffer, unsigned int *len, t_data *data)
{
	int	ret = OK;
	ret = get_group_name(strat, buffer, data->gid);
	if (ret == OK && *buffer != NULL)
	{
		*len = ft_strlen(*buffer);
	}
	else
	{
		*len = 0;
	}
	return (ret);
}

static unsigned int format_group_id(char **buffer, t_data *data)
{
	unsigned int	len = 0;
	*buffer = ft_itoa(data->gid);
	if (buffer != NULL)
	{
		len = ft_strlen(*buffer);
	}
	return (len);
}
