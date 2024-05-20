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

static char*	get_now_string();
static int		recent_month(char *time_string, char *now_string, int year_offset);
static int		recent_day(char *time_string, char *now_string);
static int		getMonth(char *time);
static int		getYear(char *time);
static int		getDay(char *time);

int	recent(char *time_string)
{
	char*	now_string = get_now_string();
	if (now_string == NULL)
	{
		return (ERROR);
	}

	int	time_year = getYear(time_string);
	int	now_year = getYear(now_string);
	int	recent = recent_month(time_string, now_string, now_year - time_year);

	return (recent);
}

static char*	get_now_string()
{
	errno = 0;
	time_t	now = time(NULL);
	if (now == -1)
	{
		perror("ft_ls: time: ");
		return (NULL);
	}

	char	*now_string = ctime(&now);
	if (now_string == NULL)
	{
		perror("ft_ls: ctime: ");
	}

	return (now_string);
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
	char	*month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  
	for (int i = 0; i < 12; ++i)
	{
		if (ft_strncmp(&time[4], month[i], 3) == 0)
		{
			return (i);
		}
	}

	return (ERROR);
}

static int	getYear(char *time)
{
	return (ft_atoi(&time[20]));
}

static int	getDay(char *time)
{
	return (ft_atoi(&time[8]));
}
