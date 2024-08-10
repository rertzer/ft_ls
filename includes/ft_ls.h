/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <rertzer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:20:47 by rertzer           #+#    #+#             */
/*   Updated: 2024/05/06 10:20:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*debug */
# include <stdio.h>

#define DP printf("%s %d\n", __FILE__, __LINE__);
/*------*/

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <grp.h>
# include <pwd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <sys/sysmacros.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>

# include "../libft/libft.h"
# include "colors.h"

/*================================ define =============================================*/
# define	OK 0
# define	MINOR_KO 1
# define	MAJOR_KO 2
# define	INTERNAL_KO 3
# define	ERROR -1
# define	TRUE 1
# define	FALSE 0

# define  FT_LS_BLOCK_SIZE 16384

# define MODES_NB 7
# define HASH_SIZE 512
# define HASH_A 2654435769
# define HASH_SHIFT 23

# define SIX_MONTH_MIN 15638400
# define SIX_MONTH_MAX 15897600
# define SIX_MONTH 15700000

# define JAN_CODE 8
# define FEB_CODE 0
# define MAR_CODE 12
# define APR_CODE 27
# define MAY_CODE 19
# define JUN_CODE 28
# define JUL_CODE 26
# define AUG_CODE 21
# define SEP_CODE 14
# define OCT_CODE 16
# define NOV_CODE 30
# define DEC_CODE 1
# define MONTH_CODE_MAX 31
# define MONTH_CODE_SHIFT 199

# define EIGHT_SPACES 0x2020202020202020;

/* ============================ Typedef ================================== */

typedef enum {REG, DIREC, CHR, BLK, FIFO, LNK, SOCK, ERROR_TYPE=-1} e_type; 

typedef struct {
	unsigned int	id;
	char			*value;
} t_id;

typedef struct {
	char	*name;
	e_type	type;
	mode_t	mode;
	bool	broken;
} t_file;

typedef struct {
	t_file				file;
	dev_t				dev;
	dev_t				rdev;
	bool				xattr;
	nlink_t				links;
	uid_t				uid;
	gid_t				gid;
	size_t				total_size;
	size_t				block_size;
	size_t				block_nb;
	struct timespec		time;
	char				*path;
	t_file				target;
}  t_data;

typedef struct {
	char			mode[12];
	char			links[20];
	char			*user;
	char			*group;
	char			size[20];
	char			minor[11];
	char			major[11];
	char			date[13];
	char			*name;
	char			*path;
	char			*target;
	e_color_type	color;
	e_color_type	target_color;
	bool			align_user_left;
	bool			align_group_left;
} t_format_data;

typedef struct {
	unsigned int	mode;
	unsigned int	links;
	unsigned int	user;
	unsigned int	group;
	unsigned int	size;
	unsigned int	minor;
	unsigned int	major;
	unsigned int	date;
	unsigned int	name;
	unsigned int	path;
} t_format_sizes;

typedef struct {
	char			*path;
	bool			valid;
	size_t			total_block_size;
	unsigned int	entry_nb;
	t_list			*content;
} t_directory;

typedef struct s_strategies {
	bool	(*keepEntry)(const struct dirent* const);
	void	(*addlist)(t_list **, t_list*);
	t_list*		(*sortingalgo)(t_list*, unsigned int, bool(*sorting)(t_data*, t_data*));
	bool	(*sorting)(t_data*, t_data*);
	bool	(*othersorting)(t_data*, t_data*);
	int		(*strcmp)(const char*, const char*);
	bool	(*isdirectory)(t_data*);
	struct timespec	(*settime)(struct stat*);
	int		(*recurse)(struct s_strategies*, t_directory*);
	int		(*printallformat)(struct s_strategies*, t_directory*, t_format_sizes*, t_format_data*);
	int		(*printformat)(struct s_strategies*, t_format_data*, t_format_sizes *, char *buffer);
	void	(*printtotal)(t_directory *dir);
	int		(*color)(e_color_type*, t_file *file);
	unsigned int	(*printuser)(char *dest, t_format_data*, t_format_sizes*, unsigned int);
	unsigned int	(*printgroup)(char *dest, t_format_data*, t_format_sizes*, unsigned int);
	bool	print_path_name;
	bool	previous_print;
	t_list*	users[HASH_SIZE];
	t_list*	groups[HASH_SIZE];
}  t_strategies;

/* ================================= Mandatory or Bonus ============================ */
# ifdef FT_LS_BONUS
#  include "ft_ls_bonus.h"
# else
#  include "ft_ls_mandatory.h"
# endif // !FT_LS_BONUS 

/*======================================================= functions =========================================================== */
// data handling
t_data			*add_new_data(t_list **lst, char const * const name, unsigned char d_type, char const * const path, void (*lstadd)(t_list**, t_list*));
t_data			*new_data();
void			data_del(void*);
bool			is_directory_simple(t_data *data);
bool			is_directory_longlist(t_data *data);
bool			is_directory_nodir(t_data *data);

// option handler
int				parse_all_args(t_options *opt, t_list **paths, int argc, char **argv);
bool			get_option(t_options *opt, char arg);
int				parse_long_option(t_options *opt, char *arg);
int				parse_short_option(t_options *opt, char *arg);
int				parse_option(t_options *opt, char arg);

//strategies
int				set_strategies(t_options *opt, t_strategies *strat);
void			option_a(t_strategies *strat, t_options *opt);
void			option_l(t_strategies *strat, t_options *opt);
void			option_r(t_strategies *strat, t_options *opt);
void			option_R(t_strategies *strat, t_options *opt); void	option_t(t_strategies *strat, t_options *opt);
void			option_time_sorting(t_strategies *strat, t_options *opt);

//color
int				no_color(e_color_type *color_type, t_file *file);
const char		*get_color_str(e_color_type color);

//sorting
int				bubble_sort(t_list* list, bool(*sorting)(t_data*, t_data*));
t_list			*merge_sort(t_list* lst, unsigned int lst_len, bool(*ordered)(t_data *a, t_data *b));
t_list			*no_sorting(t_list* lst, unsigned int lst_len, bool(*sorting)(t_data*, t_data*));
bool			sort_by_func(void *a, void *b, bool(*compare)(t_data *a, t_data *b));
bool			sort_by_name(t_data *a, t_data *b);
bool			sort_by_name_reverse(t_data *a, t_data *b);
bool			sort_by_time(t_data *a, t_data *b);
bool			sort_by_time_reverse(t_data *a, t_data *b);
int				ls_strcmp(const char *s1, const char *s2);

//keepentry
bool			keep_all(const struct dirent* const entry);
bool			skip_dot(const struct dirent* const entry);

//recursion
int				no_recursion(t_strategies *strat, t_directory *dir);
int				recursive(t_strategies *strat, t_directory *dir);

// formating
int				format(t_strategies *strat, t_directory *dir);
unsigned int	format_name(char **buffer, t_data *data);
void			print_total(t_directory *dir);
void			no_print_total(t_directory *dir);

//load format
int				load_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data * all_format_data);

// print format
int				print_all_format_data(t_strategies *strat, t_directory *dir, t_format_sizes *format_sizes, t_format_data *all_format_data);
int				print_format_data_long(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes, char *buffer);
int				print_format_data_short(t_strategies *strat, t_format_data *format_data, t_format_sizes *format_sizes, char *buffer);
unsigned int	print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
unsigned int	print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
unsigned int	no_print_format_user(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
unsigned int	no_print_format_group(char *dest, t_format_data *format_data, t_format_sizes *format_sizes, unsigned int offset);
unsigned int	print_format_color(char *dest, t_format_data *format_data, unsigned int offset);
unsigned int	print_format_name(char *dest, t_format_data *format_data, unsigned int offset);
unsigned int	print_format_color_reset(char *dest, t_format_data *format_data, unsigned int offset);
unsigned int	print_format_short_ending(char *dest, unsigned int offset);

// list_path
int				process_all_paths(t_strategies *strat, t_list **all_paths, unsigned int len);
int				default_path(t_strategies *strat);
int				list_all_files(t_strategies *strat, t_list **all_paths);
int				list_all_path(t_strategies *strat, t_list *all_paths);
int				list_path(t_strategies *strats, char* path);

//directory
void			free_directory(t_directory *dir);

// directory content
void			init_dir(t_directory *dir);
int				get_dir_content(t_strategies *strat, t_directory *dir);

// recent
int				recent(time_t time, char *time_string);

// time
struct timespec	last_modif(struct stat *stat_buffer);
struct timespec	access_time(struct stat *stat_buffer);
char			*get_time_string(time_t *time);

// stats
int				add_all_stats(t_strategies *strat, t_list *all_paths);
int				add_stats(t_strategies *strat, t_data *data);
int				compute_stats(t_strategies *strat, t_data *data);
int				get_type(mode_t	mode);

// symlink
int				add_symlink(t_data *data);

// dictonnary
int				insert_key(t_list *dict[HASH_SIZE], unsigned int key, char *value);
char*			get_value_by_key(t_list * dict[HASH_SIZE], unsigned int key);
void			init_dict(t_list *dict[HASH_SIZE]);
void			free_dict(t_list *dict[HASH_SIZE]);

//ids
void			init_ids(t_strategies *strat);
void			free_ids(t_strategies *strat);
int				get_user_name(t_strategies *strat, char **name, uid_t id);
int				get_group_name(t_strategies *strat, char **name, gid_t id);

// error handling
void			print_char_error(char *message, char param);
void			print_error_msg(char *message, char *param);
int				print_perror_msg(char *message, char *param);
int				xattr_error(t_data *data);

#endif
