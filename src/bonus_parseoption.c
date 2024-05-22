/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parseoption.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:18:08 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/22 10:18:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


int	parse_option(t_options *opt, char arg)
{
	int	ret = MAJOR_KO;

	for (int i = 0; i < SHORT_OPTIONS_NUMBER; ++i)
	{
		if (arg == opt->name[i])
		{
			opt->value[i] = true;
			ret = OK;
			break;
		}
		
	}
	if (ret == OK && arg == 'f')
	{
		opt->value[OPT_L] = false;
		opt->value[OPT_T] = false;
		opt->value[OPT_COLOR] = false;
		}

	return (ret);
}
