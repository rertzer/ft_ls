/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:25:02 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 13:27:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define BLACK "\x1b[0;30m"
# define RED "\x1b[0;31m"
# define GRN "\x1b[0;32m"
# define YEL "\x1b[0;33m"
# define BLU "\x1b[0;34m"
# define MAG "\x1b[0;35m"
# define CYN "\x1b[0;36m"
# define WHT "\x1b[0;37m"
# define RESET "\x1b[0m"

#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"

#define COLOR_DEFT	"\x1b[00;00m"		//default
#define COLOR_DIRE	"\x1b[34;01m"		//directory
#define COLOR_LINK	"\x1b[36;01m"		//sym link
#define COLOR_EXEC	"\x1b[32;01m"		//exec file
#define COLOR_ARCH	"\x1b[31;01m"		//archive file
#define COLOR_FIFO	"\x1b[33;40m"		//fifo
#define COLOR_BLNK	"\x1b[31;40m;01"	//broken link and missing files
#define COLOR_SOCK	"\x1b[35;01m"		//socket
#define COLOR_IMAG	"\x1b[35;01"		//image, video files...
#define COLOR_AUDI	"\x1b[36;00m"		//audio files...
#define COLOR_BLCK	"\x1b[33;43m;01"	//block device
#define COLOR_CHAR	"\x1b[33;43m;01"	//char device
#define COLOR_SUID	"\x1b[37;41m"		//set uid
#define COLOR_SGID	"\x1b[30;43m"		//set gid
#define COLOR_CAPA	"\x1b[30;41m"		//files whith capabilities
#define COLOR_SKDR	"\x1b[37;44m"		//sticky directory
#define COLOR_OWDR	"\x1b[34;42m"		//other writable directory
#define COLOR_SOWD	"\x1b[30;42m"		//sticky and other directory


typedef enum {
	COLOR_TYPE_DEFT,
	COLOR_TYPE_DIRE,
	COLOR_TYPE_LINK,
	COLOR_TYPE_EXEC,
	COLOR_TYPE_ARCH,
	COLOR_TYPE_FIFO,
	COLOR_TYPE_BLNK,
	COLOR_TYPE_SOCK,
	COLOR_TYPE_IMAG,
	COLOR_TYPE_AUDI,
	COLOR_TYPE_BLCK,
	COLOR_TYPE_CHAR,
	COLOR_TYPE_SUID,
	COLOR_TYPE_SGID,
	COLOR_TYPE_CAPA,
	COLOR_TYPE_SKDR,
	COLOR_TYPE_OWDR,
	COLOR_TYPE_SOWD
} e_color_type;

typedef e_color_type (*color_type_func)(t_data*);

#endif
