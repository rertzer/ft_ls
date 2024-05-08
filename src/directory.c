/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:38:58 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/08 09:39:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

void  free_directory(t_directory *dir)
{
  free(dir->path);
  dir->path = NULL;
  ft_lstclear(&dir->content, data_del);
}
