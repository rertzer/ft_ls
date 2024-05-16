/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_parse_option.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:21:52 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 11:21:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_PARSE_OPTION_H
# define MANDATORY_PARSE_OPTION_H

# define OPTIONS_NUMBER 5
# define OPTIONS "alrRt"
# define LONG_OPTIONS_NB 0
# define LONG_OPTIONS {} 

typedef enum {OPT_A, OPT_L, OPT_R, OPT_RR, OPT_T} e_option;

typedef struct {
	char	name[OPTIONS_NUMBER];
	bool	value[OPTIONS_NUMBER];
} t_options;



#endif // MANDATORY_PARSE_OPTION_H
