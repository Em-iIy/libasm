# ----------------------------------------Name
NAME = run

# ----------------------------------------Files
FILES_SRCS =	main.c \
				test.c \
				ft_read_test.c \
				ft_strlen_test.c \
				ft_strcpy_test.c \
				ft_strcmp_test.c \
				ft_strdup_test.c \
				ft_write_test.c \

FILES_OBJS = $(FILES_SRCS:.c=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/
DIR_INC = ./inc/

vpath %.c $(DIR_SRCS) \

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)


# ----------------------------------------Flags
CC = cc
# CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
# CFLAGS += -O3

INC = -Iinc

# ----------------------------------------Libraries
LIBASM = ../libasm.a

# ----------------------------------------Making
all: $(NAME)
.PHONY: all

$(NAME): $(OBJS) $(DIR_OBJS) $(LIBASM)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBASM)

$(DIR_OBJS)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(DIR_OBJS):
	mkdir -p $@


# ----------------------------------------Cleaning
clean:
	rm -f $(OBJS)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
