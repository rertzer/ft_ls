/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 09:57:52 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 09:59:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_clean(char **splited)
{
	size_t	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		++i;
	}
	free(splited);
	return (NULL);
}
