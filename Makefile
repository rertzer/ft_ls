CC := cc
FLAGS := -Wall -Wextra -Werror -g3

NAME := ft_ls 

LIBFT_DIR := libft/

SRC_DIR := src/

OBJ_DIR := obj/

INC_DIR := includes/

LIBFT := $(LIBFT_DIR)libft.a

SOURCES := \
	data.c \
	sorting.c \
	bubblesort.c \
	errors.c \
	keepentry.c \
	options.c \
	strategies.c \
	pathlisting.c \
	dircontent.c \
	main.c

OBJ := $(SOURCES:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJ))
DEPS := $(OBJS:.o=.d)


all: $(NAME) 

bonus: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c -MMD $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR) 

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -o  $@ $(OBJS) $(LIBFT) -lreadline

$(OBJ_DIR):
	mkdir  $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -fd $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean 
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re
