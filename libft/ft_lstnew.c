/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:27:33 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/13 10:47:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

  errno = 0;
	lst = malloc(sizeof(t_list));
	if (lst == NULL){
    perror("ft_ls: malloc: ");
  }
	else{
    lst->content = content;
    lst->next = NULL;
  }
	return (lst);
}
