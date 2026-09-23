# ----------------------------------------Name
NAME = libasm.a

# ----------------------------------------Files
FILES_SRCS =	ft_strlen.s \
				ft_strcpy.s \
				ft_strcmp.s \
				ft_strdup.s \
				ft_write.s \
				ft_read.s \

FILES_OBJS = $(FILES_SRCS:.s=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/

vpath %.s $(DIR_SRCS) \

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)

# ----------------------------------------Flags
CC = nasm
CFLAGS = -f elf

# ----------------------------------------Making
all:
	@$(MAKE) $(NAME) -j4
.PHONY: all

$(NAME): $(OBJS) $(DIR_OBJS)
	ar -rcs -o $(NAME) $(OBJS)

$(DIR_OBJS)%.o: %.s
	nasm -f elf64 $< -o $@

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

# ----------------------------------------run tests
run-test: all
	$(MAKE) -C test
	test/run
.PHONY: run-test
