/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:47:48 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/22 11:47:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int	get_term_width();

int	print_all_format_data_by_columns(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{

	unsigned int	col_nb = get_term_width() / format_sizes->name;
}

int	print_format_data_column(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes)
{
	(void)strat;



	const char *color = get_color_str(format_data->color);
	ft_putstr_fd(color, 1);
	ft_putstr_fd(format_data->name);

	offset += print_format_color(buffer, format_data, offset);
	offset += print_format_name(buffer, format_data, offset);
	offset += print_format_color_reset(buffer, offset);
	offset += print_format_short_ending(buffer, offset);

	write(1, buffer, offset);

	return (OK);
}

static unsigned int	get_term_width()
{
	struct winsize w_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_wsize);

    return (w_size.ws_col);
}
