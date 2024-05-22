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

unsigned int	get_term_width()
{
	struct winsize w_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_wsize);

    return (w_size.ws_col);
}
