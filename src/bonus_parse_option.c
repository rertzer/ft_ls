/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:31:02 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 11:31:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "bonus_parse_option.h"

int	parse_long_option(t_options *opt, char *arg)
{
	int		ret = MAJOR_KO;
	char	*long_options[] = LONG_OPTIONS;

	for	(int i = 0; i < LONG_OPTIONS_NB; ++i)
	{
		if (ft_strcmp(&arg[2], long_options[i]) == 0)
		{
			opt->value[i + OPTIONS_NUMBER] = true;
			ret = OK;
			break;	
		}
	}

	if (ret != OK)
	{ 
		print_error_msg("unrecognized option '", arg);
	}

	return (ret);
}

int	parse_short_option(t_options *opt, char *arg)
{
	int	ret = OK;

	for (int i = 1; arg[i] != '\0'; ++i)
	{
		ret = parse_option(opt, arg[i]);
		if (ret != OK)
		{ 
			print_char_error("invalid option -- ", arg[i]);
			break;
		}
	}

	return (ret);
}

int	parse_option(t_options *opt, char arg)
{
	int	ret = MAJOR_KO;

	for (int i = 0; i < OPTIONS_NUMBER; ++i)
	{
		if (arg == opt->name[i])
		{
			opt->value[i] = true;
			ret = OK;
			break;
		}
	}

	return (ret);
}
