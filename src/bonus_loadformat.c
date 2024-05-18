/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_loadformat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:42:31 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 13:42:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

static e_color_type	get_color_type(t_data *data);
static e_color_type	get_basic_color_type(t_data *data);
static e_color_type	get_file_color_type(t_data *data);
static e_color_type	get_direc_color_type(t_data *data);
static e_color_type	get_symlink_color_type(t_data *data);
static e_color_type	get_extension_color_type(t_data *data)

unsigned int	format_name_color(char **buffer, t_data *data)
{
	e_color_type color_type = get_color_type(data);	
}


static e_color_type	get_color_type(t_data *data)
{
	e_color_type color_type = COLOR_TYPE_DEFT;

	color_type = get_basic_color_type(data);
	if (color_type == COLOR_TYPE_DEFT)
	{
		color_type = get_file_color_type(data);
	}
	else if (color_type == COLOR_TYPE_DIRE)
	{
		color_type = get_direc_color_type(data);
	}
	else if (color_type == COLOR_TYPE_LINK)
	{
		color_type = get_symlink_color_type(data);
	}

	return (color_type);
}

static e_color_type	get_basic_color_type(t_data *data)
{	
	e_color_type color_type = COLOR_TYPE_DEFT;

	e_color_type types[] = {
		COLOR_TYPE_DEFT
		COLOR_TYPE_DIRE
		COLOR_TYPE_CHAR
		COLOR_TYPE_BLCK
		COLOR_TYPE_FIFO
		COLOR_TYPE_SOCK
	}
	return (types[data->type]);
}

static e_color_type	get_file_color_type(t_data *data)
{
	e_color_type color_type = COLOR_TYPE_DEFT;

	//TODO: capabilites
	
	if (data->mode & S_ISUID)
	{
		color_type = COLOR_TYPE_SUID;
	}
	else if (data->mode & S_ISGID)
	{
		color_type = COLOR_TYPE_SGID;
	}
	else if (data->mode & S_IXUSR || data->mode & S_IXGRP || data->mode & S_IXOTH)
	{
		color_type = COLOR_TYPE_EXEC;
	}
	else
	{
		color_type = get_extension_color_type(data);
	}

	return (color_type);
}

static e_color_type	get_direc_color_type(t_data *data)
{
	e_color_type color_type = COLOR_TYPE_DIRE;

	if (data->mode & S_ISVTX && data->mode & S_IWOTH)
	{
		color_type = COLOR_TYPE_SOWD;
	}
	else if (data->mode & S_ISVTX)
	{
		color_type = COLOR_TYPE_SKDR;
	}
	else if (data->mode & S_IWOTH)
	{
		color_type = COLOR_TYPE_OWDR;
	}

	return (color_type);
}

static e_color_type	get_symlink_color_type(t_data *data)
{
	//broken link
}

static e_color_type	get_extension_color_type(t_data *data)
{
	static const char	*archive_ext[] = {
		"tar", "tgz", "arc", "arj", "taz", "lha", "lz4", "lzh", "lzma", "tlz", "txz",
		"tzo", "t7z", "zip", "z", "dz", "gz", "lrz", "lz", "lzo", "xz", "zst", "tzst",
		"bz2", "bz", "tbz", "tbz2", "tz", "deb", "rpm", "jar", "war", "ear", "sar",
		"rar", "alz", "ace", "zoo", "cpio", "7z", "rz", "cab", "wim", "swm", "dwm",
		"esd", NULL
	};

	static const char	*image_ext[] = {
		"jpg", "jpeg", "mjpg", "mjpeg", "gif", "bmp", "pbm", "pgm", "ppm", "tga",
		"xbm", "xpm", "tif", "svg", "svgz", "mng", "pcx", "mov", "mpg", "m2v",
		"mkv", "webm", "ogm", "mp4", "m4v", "mp4v", "vob", "qt", "wmv", "asf",
		"rm", "rmvb", "flc", "avi", "fli", "flv", "gl", "dl", "xcf", "xwd",
		"yuv", "cgm", "emf", "ogv", "ogx", NULL
	};

	static const char	*audio_ext[] = {
		"aac", "au", "flac", "m4a", "mid", "midi", "mka", "mp3", "mpc", "ogg",
		"ra", "wav", "oga", "opus", "spx", "xspf", NULL
	};

	e_color_type color_type = COLOR_TYPE_DEFT;

	char *extension = ft_strrchr(data->name, '.');

	if (extension != NULL)
	{
		++extension;
		if (ft_strinset(extension, archive_ext))
		{
			color_type = COLOR_ARCH;
		}
		else if (ft_strinset(extension, image_ext))
		{
			color_type = COLOR_IMAG;
		}
		else if (ft_strinset(extension, audio_ext))
		{
			color_type = COLOR_AUDI;
		}
	}
	return (color_type);
}

