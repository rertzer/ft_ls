CC := cc
FLAGS := -Wall -Wextra -Werror -o3

NAME := libft.a

OBJ_DIR := obj/

SRC_DIR := ./

INC_DIR := ./

SOURCES := ft_atoi.c	\
	ft_buffercpy.c \
	ft_bufferncpy.c \
	ft_bzero.c	\
	ft_calloc.c	\
	ft_is_inset.c \
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isascii.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_itoa.c	\
	ft_itoa_dec.c \
	ft_memchr.c	\
	ft_malloc.c \
	ft_memcmp.c	\
	ft_memcpy.c	\
	ft_memmove.c	\
	ft_memset.c	\
	ft_putchar_fd.c	\
	ft_putendl_fd.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_split.c	\
	ft_split_clean.c \
	ft_strchr.c	\
	ft_strcpy.c \
	ft_strdup.c	\
	ft_striteri.c	\
	ft_strjoin.c	\
	ft_pathjoin.c	\
	ft_strinset.c \
	ft_strlcat.c	\
	ft_strlcpy.c	\
	ft_strlen.c	\
	ft_strmapi.c	\
	ft_strncmp.c	\
	ft_strcmp_ci.c	\
	ft_strcmp_local.c	\
	ft_strcmp.c	\
	ft_strnstr.c	\
	ft_strrchr.c	\
	ft_strtrim.c	\
	ft_substr.c	\
	ft_tolower.c	\
	ft_toupper.c

SOURCES_BONUS := ft_lstadd_back.c	\
ft_lstadd_front.c	\
	ft_lstclear.c	\
	ft_lstdelone.c	\
	ft_lstiter.c	\
	ft_lstlast.c	\
	ft_lstmap.c	\
	ft_lstnew.c	\
	ft_lstsize.c \

INC := libft.h

OBJ := $(SOURCES:.c=.o)

OBJ_BONUS := $(SOURCES_BONUS:.c=.o)

OBJS := $(addprefix $(OBJ_DIR), $(OBJ))
OBJS_BONUS := $(addprefix $(OBJ_DIR), $(OBJ_BONUS))

INCS := $(addprefix $(INC_DIR), $(INC))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS) $(INCS)
	ar cr $@ $(OBJS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

bonus: $(NAME) $(OBJS_BONUS)
	ar r $(NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	rm -fd $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all bonus clean fclean re

