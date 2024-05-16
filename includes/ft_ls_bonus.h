/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:31:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 10:32:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_BONUS_H
# define FT_LS_BONUS_H

# include <termios.h>

# include "ft_ls.h"
# include "bonus_parse_option.h"

// bonus strategies
void	option_d(t_strategies *strat, t_options *opt);
void	option_f(t_strategies *strat, t_options *opt);
void	option_g(t_strategies *strat, t_options *opt);
void	option_G(t_strategies *strat, t_options *opt);
void	option_u(t_strategies *strat, t_options *opt);
void	option_color(t_strategies *strat, t_options *opt);

#endif // !FT_LS_BONUS_H
