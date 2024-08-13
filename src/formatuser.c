/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatuser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:08:16 by rertzer           #+#    #+#             */
/*   Updated: 2024/08/13 13:08:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


static int format_user_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data);
static unsigned int format_user_id(char **buffer, t_data *data);

int	format_user(t_strategies *strat, t_format_data *format_data, unsigned int *size, t_data *data)
{
	int	ret = format_user_user(strat, &format_data->user, size, data);
	if (ret == INTERNAL_KO)
	{
		return (ret);
	}
	if (*size == 0)
	{
		*size = format_user_id(&format_data->user, data);
		if (*size == 0)
		{
			return (INTERNAL_KO);
		}
		format_data->align_user_left = false;
	}
	
	return (ret);
}

static int format_user_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data)
{
	int	ret = OK;

	ret = get_user_name(strat, buffer, len, data->uid);

	return (ret);
}

static unsigned int format_user_id(char **buffer, t_data *data)
{
	unsigned int	len = 0;
	*buffer = ft_itoa(data->uid);
	if (buffer != NULL)
	{
		len = ft_strlen(*buffer);
	}
	return (len);
}
