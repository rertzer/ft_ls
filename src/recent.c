/* *****:warn("%s");********************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:27 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/13 18:07:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	get_now();
static void		get_now_string(char *now_string, time_t now);
static int		recent_month(char *time_string, char *now_string, int year_offset);
static int		recent_day(char *time_string, char *now_string);
static int		getMonth(char *time);
static int		getYear(char *time);
static int		getDay(char *time);

int	recent(time_t time, char *time_string)
{
	static char	now_string[26];

	time_t	now = get_now();

	if (time_string == NULL)
	{
		get_now_string(now_string, now);
		if (now_string[0] == '\0')
		{
			return (INTERNAL_KO);
		}
		else
		{
			return (OK);
		}
	}
	time_t	diff = now - time;
	if (diff < SIX_MONTH_MIN)
	{
		return (true);
	}
	else if (diff > SIX_MONTH_MAX)
	{
		return (false);
	}

	get_now_string(now_string, now);

	if (now_string[0] == '\0')
	{
		return (ERROR);
	}

	int	time_year = getYear(time_string);
	int	now_year = getYear(now_string);
	int	recent = recent_month(time_string, now_string, now_year - time_year);

	return (recent);
}

static	time_t	get_now()
{
	static	time_t	now;

	if (now == 0)
	{
		errno = 0;
		now = time(NULL);
		if (now == -1)
		{
			perror("ft_ls: time: ");
		}
	}
	return (now);
}

static void	get_now_string(char *now_string, time_t now)
{
	errno = 0;

	if (now_string[0] == '\0')
	{
		char *now_tmp = ctime(&now);
		if (now_tmp == NULL)
		{
			perror("ft_ls: ctime: ");
		}
		else
		{
			ft_strcpy(now_string, now_tmp);
		}
	}
}

static int	recent_month(char *time_string, char *now_string, int year_offset)
{
	int	recent = FALSE;
	int	time_month = getMonth(time_string);
	int	now_month = getMonth(now_string);
	int	month_ago = now_month - time_month + 12 * year_offset;

	if (month_ago < 6)
	{
		recent = TRUE;
	}
	else if (month_ago == 6)
	{
		recent = recent_day(time_string, now_string);
	}

	return (recent);
}

static int	recent_day(char *time_string, char *now_string)
{
	int	recent = FALSE;
	int	time_day = getDay(time_string);
	int	now_day = getDay(now_string);

	if (time_day >= now_day)
	{
		recent = TRUE;
	}
	return (recent);
}

static int	getMonth(char *time)
{
	static int	month_index[MONTH_CODE_MAX];
	
	if (month_index[FEB_CODE] == 0)
	{
		month_index[JAN_CODE] = 0;
		month_index[FEB_CODE] = 1;
		month_index[MAR_CODE] = 2;
		month_index[APR_CODE] = 3;
		month_index[MAY_CODE] = 4;
		month_index[JUN_CODE] = 5;
		month_index[JUL_CODE] = 6;
		month_index[AUG_CODE] = 7;
		month_index[SEP_CODE] = 8;
		month_index[OCT_CODE] = 9;
		month_index[NOV_CODE] = 10;
		month_index[DEC_CODE] = 11;
	}

	int	month_code = time[5] + time[6] - MONTH_CODE_SHIFT;

	return (month_index[month_code]);
}

static int	getYear(char *time)
{
	return (ft_atoi(&time[20]));
}

static int	getDay(char *time)
{
	return (ft_atoi(&time[8]));
}
