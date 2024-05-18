/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse_option.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:22:06 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 11:22:08 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PARSE_OPTION_H
# define BONUS_PARSE_OPTION_H

# define SHORT_OPTIONS_NUMBER 10
# define SHORT_OPTIONS "adfgGlrRtu"
# define LONG_OPTIONS_NUMBER 1
# define LONG_OPTIONS {"color"}
# define OPTIONS_NUMBER (SHORT_OPTIONS_NUMBER + LONG_OPTIONS_NUMBER)

typedef enum {OPT_A, OPT_D, OPT_F, OPT_G, OPT_GG, OPT_L, OPT_R, OPT_RR, OPT_T, OPT_U, OPT_COLOR} e_option;

typedef struct {
	char	name[OPTIONS_NUMBER];
	bool	value[OPTIONS_NUMBER];
} t_options;


#endif // !BONUS_PARSE_OPTION_H

