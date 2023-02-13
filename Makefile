NAME					:= pipex

UNAME_S					:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  FSANITIZELEAK			:= -fsanitize=leak
  FRAMEWORK				:=
  LINUX_LIBS			:=
  LINUX_INCLUDES		:= -I/usr/include
  OS_FLAG				:= -D LINUX
else
  FSANITIZELEAK			:=
  FRAMEWORK				:=
  LINUX_LIBS			:=
  LINUX_INCLUDES		:=
  OS_FLAG				:= -D OSX
endif

ifndef addressoff
	FSANADDRESS			:= -fsanitize=address
else
	FSANADDRESS			:=
endif

ifndef fsanitizeoff
	FSANITIZE			:= -fno-omit-frame-pointer -fstack-protector-all $(FSANADDRESS) $(FSANITIZELEAK)
else
	FSANITIZE			:=
endif

ifdef DEBUG
	DEVFLAGS			:= -ggdb -O0 $(FSANITIZE)
else
	DEVFLAGS			:=
endif

CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -pedantic -O3 $(DEVFLAGS) $(OS_FLAG)
RM						:= rm -f

LIB_DIRECTORY			:= ./libs/

LIBFT					:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS			:= $(LIBFT_DIRECTORY)includes/

LIBPRINTF				:= $(LIBPRINTF_DIRECTORY)libftprintf.a
LIBPRINTF_DIRECTORY		:= $(LIB_DIRECTORY)libprintf/
LIBPRINTF_HEADERS		:= $(LIBPRINTF_DIRECTORY)includes/

INCLUDE_DIR				:= ./includes/

# lm: default math lib
LIBRARIES				:= -lftprintf -lft -L. -L$(LIBFT_DIRECTORY) -L$(LIBPRINTF_DIRECTORY) $(FRAMEWORK) $(LINUX_LIBS)
INCLUDES				:= -I$(LIBFT_HEADERS) -I$(LIBPRINTF_HEADERS) -I$(INCLUDE_DIR) $(LINUX_INCLUDES)

SOURCES_DIRECTORY		:= ./sources/
SOURCES_LIST			:= main.c\
							init.c\
							arg_handle.c\
							handle_files.c
HEADER_LIST				:= pipex.h
HEADER_FILES			:= $(addprefix $(INCLUDE_DIR), $(HEADER_LIST))

OBJECTS_DIRECTORY		:= objects/
OBJECTS_LIST			:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS					:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))


.PHONY: all clean fclean re docker_build docker_run docker_clean

all: $(NAME)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(NAME): Creating $(LIBFT)..."
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(LIBPRINTF):
	@echo "$(NAME): Creating $(LIBPRINTF)..."
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY)

$(NAME): $(LIBFT) $(LIBPRINTF) $(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)


clean:
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


clean_pipex:
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM


fclean: clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	rm -f $(NAME)

docker_build:
	docker build -t $(NAME) .

docker_run:
	docker run -it $(NAME)

docker_clean:
	docker system prune -a --volumes

re: fclean all

re_pipex: clean_pipex all

norm:
	norminette includes/ sources/ libs/libft/ libs/libprintf/ 

funcs: $(NAME) $(BONUS_NAME))
	@echo "Functions used in $(NAME):"
	nm -u $(NAME)
	@echo "Functions used in $(BONUS_NAME):"
	nm -u $(BONUS_NAME)

francinette_lft:
	cd libs/libft && cp includes/libft.h .
	cd libs/libft && ~/francinette/tester.sh
	cd libs/libft && rm libft.h
