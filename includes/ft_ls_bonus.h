/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:31:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 13:27:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_BONUS_H
# define FT_LS_BONUS_H

# include <sys/ioctl.h>

# include "ft_ls.h"
# include "bonus_parse_option.h"


#define COLUMN_MIN_SPACE 2


typedef struct	{
	unsigned int	line_nb;
	unsigned int	col_nb;
	unsigned int	full_lines;
	unsigned int	term_width;
	unsigned int	*col_sizes;
}	t_column;

// bonus strategies
void	option_d(t_strategies *strat, t_options *opt);
void	option_f(t_strategies *strat, t_options *opt);
void	option_g(t_strategies *strat, t_options *opt);
void	option_G(t_strategies *strat, t_options *opt);
void	option_u(t_strategies *strat, t_options *opt);
void	option_color(t_strategies *strat, t_options *opt);

// bonus formating
int	format_color(e_color_type *color_type, t_file *file);

// bonus colums
int	print_all_format_data_column(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data);

#endif // !FT_LS_BONUS_H
