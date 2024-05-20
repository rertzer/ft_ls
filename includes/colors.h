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

#define RESET_SIZE 4

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
#define COLOR_BKLN	"\x1b[31;40;01m"	//broken link and missing files
#define COLOR_SOCK	"\x1b[35;01m"		//socket
#define COLOR_IMAG	"\x1b[35;01m"		//image, video files...
#define COLOR_AUDI	"\x1b[36;00m"		//audio files...
#define COLOR_BLCK	"\x1b[33;43;01m"	//block device
#define COLOR_CHAR	"\x1b[33;43;01m"	//char device
#define COLOR_SUID	"\x1b[37;41m"		//set uid
#define COLOR_SGID	"\x1b[30;43m"		//set gid
#define COLOR_CAPA	"\x1b[30;41m"		//files whith capabilities
#define COLOR_SKDR	"\x1b[37;44m"		//sticky directory
#define COLOR_OWDR	"\x1b[34;42m"		//other writable directory
#define COLOR_SOWD	"\x1b[30;42m"		//sticky and other directory


#define COLOR_TYPE_NUMBER 18
typedef enum {
	COLOR_TYPE_DEFT,	//default
	COLOR_TYPE_DIRE,	//directory
	COLOR_TYPE_LINK,	//sym link
	COLOR_TYPE_EXEC,	//exec file
	COLOR_TYPE_ARCH,	//archive file
	COLOR_TYPE_FIFO,	//fifo
	COLOR_TYPE_BKLN,	//broken link and missing files
	COLOR_TYPE_SOCK,	//socket
	COLOR_TYPE_IMAG,	//image, video files...
	COLOR_TYPE_AUDI,	//audio files...
	COLOR_TYPE_BLCK,	//block device
	COLOR_TYPE_CHAR,	//char device
	COLOR_TYPE_SUID,	//set uid
	COLOR_TYPE_SGID,	//set gid
	COLOR_TYPE_CAPA,	//files whith capabilities
	COLOR_TYPE_SKDR,	//sticky directory
	COLOR_TYPE_OWDR,	//other writable directory
	COLOR_TYPE_SOWD 	//sticky and other directory
} e_color_type;

#endif
