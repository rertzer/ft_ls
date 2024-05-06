/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:58:14 by rertzer           #+#    #+#             */
/*   Updated: 2024/03/16 10:37:42 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char delimiter);
static char	**split_string(char **splited, char const *s, char delimiter);
static int	get_next_word_index(char const *str, char delimiter, int i);
static int	get_word_end_index(char const *str, char delimiter, int i);

char	**ft_split(char const *str, char delimiter)
{
	int		word_nb;
	char	**splited;

	if (NULL == str)
		return (NULL);
	word_nb = word_count(str, delimiter);
	splited = malloc(sizeof(char *) * (word_nb + 1));
	if (NULL == splited)
		return (NULL);
	splited[word_nb] = NULL;
	return (split_string(splited, str, delimiter));
}

static int	word_count(char const *str, char delimiter)
{
	int		i;
	int		word_nb;
	bool	is_word;

	word_nb = 0;
	is_word = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_word && str[i] == delimiter)
				is_word = false;
		else if (is_word == false && str[i] != delimiter)
		{
			is_word = true;
			word_nb++;
		}
		++i;
	}
	return (word_nb);
}

static char	**split_string(char **splited, char const *str, char delimiter)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;

	i = 0;
	end = 0;
	len = ft_strlen(str);
	while (end < len)
	{
		start = get_next_word_index(str, delimiter, end);
		if (start >= len)
			break ;
		end = get_word_end_index(str, delimiter, start);
		splited[i] = ft_substr(str, start, end - start);
		if (NULL == splited[i])
			return (ft_split_clean(splited));
		++i;
	}
	return (splited);
}

static int	get_next_word_index(char const *str, char delimiter, int i)
{
	while (str[i] == delimiter)
	{
		++i;
	}
	return (i);
}

static int	get_word_end_index(char const *str, char delimiter, int i)
{
	while (str[i] != delimiter && str[i] != '\0')
	{
		++i;
	}
	return (i);
}
