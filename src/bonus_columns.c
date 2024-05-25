/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_columns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:47:48 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/22 11:47:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_format_data_line(char *buffer, int line_index, int line_nb, int line_entries, t_format_data *all_format_data);
static unsigned int	print_format_data_column(char *buffer, int offset, t_format_data *format_data);
static unsigned int	get_term_width();

int	print_all_format_data_column(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	(void)strat;

	int				ret = OK;
	unsigned int	line_entries = 0;
	unsigned int	remaining_entries = dir->entry_nb;
	unsigned int	term_width = get_term_width();
	unsigned int	col_nb = term_width / (format_sizes->name + COLUMN_MIN_SPACE);
	unsigned int	line_nb = (dir->entry_nb / col_nb) + !!(dir->entry_nb % col_nb);
	unsigned int	buffer_size = term_width + col_nb * COLOR_CHAR_NB + 1;
	
	char	*buffer = ft_malloc(buffer_size + 1);
	if (buffer == NULL)
	{
		return (INTERNAL_KO);
	}
	buffer[buffer_size] = '\0';
	for (unsigned int line_index = 0; line_index < line_nb; ++line_index)
	{
		ft_memset(buffer, ' ', buffer_size);

		line_entries =  remaining_entries < col_nb ? remaining_entries : col_nb;
		remaining_entries -= line_entries;

		printf("entries: %u %u\n", line_entries, remaining_entries);
		ret = print_format_data_line(buffer, line_index, line_nb, line_entries, all_format_data);
		if (ret == INTERNAL_KO)
			break;
	}
	free(buffer);
	return (ret);
}

static int	print_format_data_line(char *buffer, int line_index, int line_nb, int line_entries, t_format_data *all_format_data)
{
	unsigned int	offset;

	printf("index: %u, nb: %u, entries: %u\n", line_index, line_nb, line_entries);
	for (int col_index = 0; col_index < line_entries; ++col_index)
	{
		printf("%u %u %u INDEX %u\n", line_index, col_index, line_nb, line_index + col_index * line_nb);
		offset = print_format_data_column(buffer, offset, &all_format_data[line_index + col_index * line_nb]);
	}

	offset += print_format_short_ending(buffer, offset);

	printf("B %u %s %zu\n", offset, buffer, strlen(buffer));
	write(1, buffer, offset -1);
	printf("C %u %s\n", offset, buffer);

	return (OK);
}

static unsigned int	print_format_data_column(char *buffer, int offset, t_format_data *format_data)
{

	offset += print_format_color(buffer, format_data, offset);
	offset += print_format_name(buffer, format_data, offset);
	offset += print_format_color_reset(buffer, offset);

	return (offset);
}

static unsigned int	get_term_width()
{
	struct winsize w_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_size);

    return (w_size.ws_col);
}
