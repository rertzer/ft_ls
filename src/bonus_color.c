/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:42:31 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/16 13:42:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static e_color_type get_color_type(t_file *file);
static e_color_type get_basic_color_type(t_file *file);
static e_color_type get_file_color_type(t_file *file);
static e_color_type get_direc_color_type(t_file *file);
static e_color_type get_symlink_color_type(t_file *file);
static e_color_type get_extension_color_type(t_file *file);

int format_color(e_color_type *color, t_file *file) {
  *color = get_color_type(file);
  return (OK);
}

static e_color_type get_color_type(t_file *file) {
  e_color_type color_type = COLOR_TYPE_DEFT;

  color_type = get_basic_color_type(file);

  if (file->mode == UINT_MAX) {
    if (color_type == COLOR_TYPE_DEFT) {
      color_type = get_extension_color_type(file);
    }
  } else {
    switch (color_type) {
    case COLOR_TYPE_DEFT:
      color_type = get_file_color_type(file);
      break;
    case COLOR_TYPE_DIRE:
      color_type = get_direc_color_type(file);
      break;
    case COLOR_TYPE_LINK:
      color_type = get_symlink_color_type(file);
      break;
    default:
      break;
    }
  }

  return (color_type);
}

static e_color_type get_basic_color_type(t_file *file) {
  int type = file->type;

  if (type >= MODES_NB || type < 0) {
    type = 7;
  }

  e_color_type types[] = {COLOR_TYPE_DEFT, COLOR_TYPE_DIRE, COLOR_TYPE_CHAR,
                          COLOR_TYPE_BLCK, COLOR_TYPE_FIFO, COLOR_TYPE_LINK,
                          COLOR_TYPE_SOCK, COLOR_TYPE_BKLN};
  return (types[type]);
}

static e_color_type get_file_color_type(t_file *file) {
  e_color_type color_type = COLOR_TYPE_DEFT;

  if (file->mode & S_ISUID) {
    color_type = COLOR_TYPE_SUID;
  } else if (file->mode & S_ISGID) {
    color_type = COLOR_TYPE_SGID;
  } else if (file->mode & S_IXUSR || file->mode & S_IXGRP ||
             file->mode & S_IXOTH) {
    color_type = COLOR_TYPE_EXEC;
  } else {
    color_type = get_extension_color_type(file);
  }

  return (color_type);
}

static e_color_type get_direc_color_type(t_file *file) {
  e_color_type color_type = COLOR_TYPE_DIRE;

  if (file->mode & S_ISVTX && file->mode & S_IWOTH) {
    color_type = COLOR_TYPE_SOWD;
  } else if (file->mode & S_ISVTX) {
    color_type = COLOR_TYPE_SKDR;
  } else if (file->mode & S_IWOTH) {
    color_type = COLOR_TYPE_OWDR;
  }

  return (color_type);
}

static e_color_type get_symlink_color_type(t_file *file) {
  e_color_type color_type = COLOR_TYPE_LINK;

  if (file->broken == true) {
    color_type = COLOR_TYPE_BKLN;
  }

  return (color_type);
}

static e_color_type get_extension_color_type(t_file *file) {
  static const char *archive_ext[] = {ARCHIVE_EXT, NULL};
  static const char *image_ext[] = {IMAGE_EXT, NULL};
  static const char *audio_ext[] = {AUDIO_EXT, NULL};

  e_color_type color_type = COLOR_TYPE_DEFT;

  char *extension = ft_strrchr(file->name, '.');

  if (extension != NULL) {
    ++extension;
    if (ft_strinset(extension, archive_ext)) {
      color_type = COLOR_TYPE_ARCH;
    } else if (ft_strinset(extension, image_ext)) {
      color_type = COLOR_TYPE_IMAG;
    } else if (ft_strinset(extension, audio_ext)) {
      color_type = COLOR_TYPE_AUDI;
    }
  }
  return (color_type);
}
