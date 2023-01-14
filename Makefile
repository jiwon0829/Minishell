CC = cc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

# 클러스터
# READLINE_LIB = -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib
# READLINE_INC = -I/goinfre/$(USER)/.brew/opt/readline/include

# MAC 인텔
# READLINE_LIB = -lreadline -L/usr/local/opt/readline/lib
# READLINE_INC = -I/usr/local/opt/readline/include

LIBFT = libft/libft.a

NAME = minishell

INC_DIR = include
INC_FILES := minishell.h envp.h
INC_FILES := $(addprefix $(INC_DIR)/, $(INC_FILES))

INC_TYPES_DIR = $(INC_DIR)/types
INC_TYPES := t_minishell.h t_envp.h t_cmd.h
INC_TYPES := $(addprefix $(INC_TYPES_DIR)/, $(INC_TYPES))

SRCS = src/utils/error_message.c src/utils/setting.c \
		src/minishell.c src/main_loop.c 

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INC_FILES) $(INC_TYPES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC)

$(LIBFT):
	@make -C ./libft

%.o: %.c
	@$(CC) $(CFLAGS) $(READLINE_INC) -I$(INC_DIR) -I$(INC_TYPES_DIR) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME) $(OBJS)

re: fclean 
	@$(MAKE)