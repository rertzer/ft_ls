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

static unsigned int	*get_file_sizes(t_directory *dir);
static unsigned int	get_max_columns(unsigned int *file_sizes, unsigned int nb, unsigned int term_width);
static int	set_columns(t_column *column, unsigned int *file_sizes, unsigned int nb, unsigned int max_col);
static int	set_column_number(t_column *column, unsigned int *file_sizes, unsigned int file_nb, unsigned int col_nb);
static void	init_column(t_column *column, unsigned int file_nb, unsigned int col_nb);
static unsigned int	get_col_id(t_column *column, unsigned int i);
static int	print_format_data_line(char *buffer, int line_index, t_column *column, t_format_data *all_format_data);
static inline unsigned int	get_line_col_nb(t_column *column, unsigned int line_index);
static unsigned int	print_format_data_column(char *buffer, int offset, t_format_data *format_data);
static unsigned int	get_term_width();

int	print_all_format_data_column(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data)
{
	(void)strat;

	int				ret = OK;
	unsigned int	line_entries = 0;
	unsigned int	remaining_entries = dir->entry_nb;
	
	t_column		column = get_column(dir);
	if (column.col_nb == 0)
	{
		return (INTERNAL_KO);
	}

	unsigned int	buffer_size = column.term_width + col_nb * COLOR_CHAR_NB + 1;
	
	char	*buffer = ft_malloc(buffer_size + 1);
	if (buffer == NULL)
	{
		return (INTERNAL_KO);
	}
	buffer[buffer_size] = '\0';
	for (unsigned int line_index = 0; line_index < column.line_nb; ++line_index)
	{
		ft_memset(buffer, ' ', buffer_size);

		line_entries =  remaining_entries < column.col_nb ? remaining_entries : column.col_nb;
		remaining_entries -= line_entries;

		printf("entries: %u %u\n", line_entries, remaining_entries);
		ret = print_format_data_line(buffer, line_index, &column, all_format_data);
		if (ret == INTERNAL_KO)
			break;
	}
	free(column.col_sizes);
	free(buffer);
	return (ret);
}


static	t_column	get_column(t_directory *dir)
{
	t_column		column;
	column.col_nb = 0;
	column.col_sizes = NULL;
	column.term_width = get_term_width();

	unsigned int	file_sizes = get_file_sizes(dir);
	if (file_sizes = NULL)
		return (column);

	unsigned int	max_col = get_max_columns(file_sizes, dir->entry_nb, column->term_width);	
	set_columns(&column, file_sizes, dir->entry_nb, max_col);

	free(file_sizes);

	return (column);
}

static unsigned int	*get_file_sizes(t_directory *dir)
{
	t_data	*data = NULL;
	t_list	*lst = dir->content;

	unsigned int	*file_sizes = ft_malloc(sizeof(unsigned int) * dir->entry_nb);
	if (file_sizes == NULL)
	{
		return (NULL);
	}

	for (int i = 0; i < dir->entry_nb; ++i)
	{
		data = (data*)lst->content;
		file_sizes[i] = ft_strlen(data->file.name);
		lst = lst->next;
	}

	return (file_sizes);
}

static unsigned int	get_max_columns(unsigned int *file_sizes, unsigned int nb, unsigned int term_width)
{
	unsigned int	min_name_size = 256;

	for (int i = 0; i < nb; ++i)
	{
		if (file_sizes[i] < min_name_size)
		{
			min_name_size = file_sizes[i];
		}
	}
	
	unsigned int	max_col = term_width / (min_name_size + COLUMN_MIN_SPACE);

	max_col = max_col < nb ? max_col : nb;

	return (max_col);
}
	
static int	set_columns(t_column *column, unsigned int *file_sizes, unsigned int nb, unsigned int max_col)
{
	unsigned int	*col_sizes = ft_malloc(sizeof(unsigned int) * max_col);
	if (col_sizes == NULL)
	{
		return (INTERNAL_KO);
	}
	
	for (unsigned int i = max_col; i > 0; --i)
	{
		if (set_column_number(column, file_sizes, nb, i) == TRUE)
			break;
	}
	return (OK);
}

static int	set_column_number(t_column *column, unsigned int *file_sizes, unsigned int file_nb, unsigned int col_nb)
{
	int				ret = FALSE;
	unsigned int	width = 0;

	init_column(column, file_nb, col_nb);

	for (unsigned int i = 0; i < file_nb; ++i)
	{
		unsigned int	col_id = get_col_id(column, i);
		if (column->col_sizes[col_id] < file_sizes[i])
		{
			column->col_sizes[col_id] = file_sizes[i];
		}
	}

	for (unsigned int i = 0; i < col_nb; ++i)
	{
		width += column->col_sizes[i] + COLUMN_MIN_SPACE;
	}

	if (width <= column->term_width)
	{
		ret = TRUE;
	}
	
	return (ret);
}

static void	init_column(t_column *column, unsigned int file_nb, unsigned int col_nb)
{
	column->col_nb = col_nb;
	column->line_nb = (file_nb / col_nb) + !!(file_nb % col_nb);
	column->full_col_nb = file_nb % col_nb;
	if (column->full_col_nb == 0)
	{
		column->full_col_nb = col_nb;
	}

	for (int i = 0; i < col_nb; ++i)
	{
		column->col_sizes[i] = 0;
	}
}

static unsigned int	get_col_id(t_column *column, unsigned int i)
{
	unsigned int	col_id = 0;
	unsigned int	full_col_max = column->line_nb * (column->full_col_nb + 1) - 1;

	++i;

	if (i <= full_col_max)
	{
		col_id = i / column->line_nb;
	}
	else
	{
		col_id = full_col_nb + 1;
		col_id += (i - full_col_max) / (column->line_nb - 1);
	}

	return (col_id);
}

static unsigned int	get_file_id(t_column *column, unsigned int line, unsigned int col)
{
	unsigned int	id;

	if (col <= column->full_col_nb)
	{
		id = col * column->line_nb + line;
	}
	else
	{
		id = column->line_nb * column->full_col_nb;
		id += (col - column->full_col_nb) * (column->line_nb - 1) + line;
	}

	return (id);
}

static int	print_format_data_line(char *buffer, int line_index, t_column *column, t_format_data *all_format_data)
{
	unsigned int	offset;
	unsigned int	col_nb = get_line_col_nb(column, line_index);


	for (int col_index = 0; col_index < col_nb; ++col_index)
	{
		unsigned int	file_id = get_file_id(column, line_index, col_index);
		offset = print_format_data_column(buffer, offset, column->col_sizes[col_index],&all_format_data[file_id]);
	}

	offset += print_format_short_ending(buffer, offset);

	write(1, buffer, offset -1);

	return (OK);
}

static inline unsigned int	get_line_col_nb(t_column *column, unsigned int line_index)
{
	unsigned int	col_nb;

	if (line_index + 1 == column.line_nb)
	{
		col_nb = column.full_col_nb;
	}
	else
	{
		col_nb = column.col_nb;
	}

	return (col_nb);
}

static unsigned int	print_format_data_column(char *buffer, unsigned int offset, unsigned int col_size, t_format_data *format_data)
{
	unsigned int	name_size;

	offset += print_format_color(buffer, format_data, offset);
	name_size = print_format_name(buffer, format_data, offset);
	offset += name_size;
	offset += print_format_color_reset(buffer, offset);
	offset += col_size - name_size;

	return (offset);
}

static unsigned int	get_term_width()
{
	struct winsize w_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w_size);

	return (w_size.ws_col);
}
