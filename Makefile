CC := cc
FLAGS := -Wall -Wextra -Werror -o3

NAME := ft_ls 

NAME_BONUS := ft_ls_bonus

LIBFT_DIR := libft/

SRC_DIR := src/

OBJ_DIR := obj/
OBJ_DIR_BONUS := obj_bonus/

INC_DIR := includes/

LIBFT := $(LIBFT_DIR)libft.a

SOURCES := \
	color.c \
	data.c \
	dictionnary.c \
	directory.c \
	ids.c \
	format.c \
	sorting.c \
	errors.c \
	keepentry.c \
	listpath.c \
	loadformat.c \
	loadformatdatavalid.c \
	formatmode.c \
	formatmiscellaneous.c \
	formatuser.c \
	formatgroup.c \
	formatinvalid.c \
	mergesort.c \
	options.c \
	parseoption.c \
	printformat.c \
	recent.c \
	status.c \
	strategies.c \
	pathlisting.c \
	recursion.c \
	stats.c \
	symlink.c \
	time.c \
	dircontent.c \
	main.c

SOURCES_MANDATORY := \
	mandatory_parseoption.c \
	mandatory_set_strategies.c \
	mandatory_strcmp.c

SOURCES_BONUS := \
	bonus_color.c \
	bonus_columns.c \
	bonus_parseoption.c \
	bonus_set_strategies.c \
	bonus_strategies.c \
	bonus_strcmp.c

SOURCES_BONUS += $(SOURCES)

OBJ_BONUS := $(SOURCES_BONUS:.c=.o)
OBJS_BONUS := $(addprefix $(OBJ_DIR_BONUS), $(OBJ_BONUS))
DEPS_BONUS := $(OBJS_BONUS:.o=.d)

OBJ_MANDATORY := $(SOURCES_MANDATORY:.c=.o)
OBJS_MANDATORY := $(addprefix $(OBJ_DIR), $(OBJ_MANDATORY))
DEPS_MANDATORY := $(OBJS_MANDATORY:.o=.d)

OBJ := $(SOURCES:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJ))
DEPS := $(OBJS:.o=.d)


all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -DFT_LS_BONUS -c -MMD $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c -MMD $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR) 

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS) $(OBJS_MANDATORY)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(OBJS_MANDATORY) $(LIBFT)

$(NAME_BONUS): $(OBJ_DIR_BONUS) $(LIBFT) $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $@ $(OBJS_BONUS) $(LIBFT)

$(OBJ_DIR):
	mkdir  $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	mkdir  $(OBJ_DIR_BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -f $(OBJS_MANDATORY)
	rm -f $(DEPS)
	rm -f $(DEPS_BONUS)
	rm -f $(DEPS_MANDATORY)
	rm -fd $(OBJ_DIR)
	rm -fd $(OBJ_DIR_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean 
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

-include $(DEPS) $(DEPS_BONUS) $(DEPS_MANDATORY)

.PHONY: all bonus clean fclean re
