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


static int			format_user_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data);
static unsigned int format_user_id(t_format_data *format_data, t_data *data);

int	format_user(t_strategies *strat, t_format_data *format_data, unsigned int *format_size, t_data *data)
{
	unsigned int size = 0;

	int	ret = format_user_user(strat, &format_data->user, &size, data);
	if (ret != INTERNAL_KO)
	{
		if (size == 0)
		{
			size = format_user_id(format_data, data);
			if (size == 0)
			{
				ret = INTERNAL_KO;
			}
		}
		set_max_size(format_size, size);
	}

	return (ret);
}

static int format_user_user(t_strategies *strat, char **buffer, unsigned int *len, t_data *data)
{
	int	ret = get_user_name(strat, buffer, len, data->uid);

	return (ret);
}

static unsigned int format_user_id(t_format_data *format_data, t_data *data)
{
	unsigned int	len = 0;

	format_data->user = ft_itoa(data->uid);
	if (format_data->user != NULL)
	{
		len = ft_strlen(format_data->user);
		format_data->align_user_left = false;
	}

	return (len);
}
