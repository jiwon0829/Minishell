CC = cc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

# 클러스터
#  READLINE_LIB = -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib
#  READLINE_INC = -I/goinfre/$(USER)/.brew/opt/readline/include

# MAC 인텔
 READLINE_LIB = -lreadline -L/usr/local/opt/readline/lib
 READLINE_INC = -I/usr/local/opt/readline/include

LIBFT = libft/libft.a

NAME = minishell

INC_DIR = include
INC_FILES := minishell.h envp.h
INC_FILES := $(addprefix $(INC_DIR)/, $(INC_FILES))

INC_TYPES_DIR = $(INC_DIR)/types
INC_TYPES := t_minishell.h t_envp.h t_cmd.h
INC_TYPES := $(addprefix $(INC_TYPES_DIR)/, $(INC_TYPES))

LIBFT_DIR = libft

SRCS = src/test_code.c \
		src/utils/error_message.c src/utils/setting.c \
		src/minishell.c src/main_loop.c  \
		src/envp/setting.c src/envp/node.c src/envp/print.c\
		src/builtin/builtin.c src/builtin/echo.c src/builtin/env.c \
		src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c \
		src/builtin/exit.c \
		src/signal/setting.c \
		src/lexer/lexer_free.c src/lexer/lexer_util.c \
		src/lexer/tokenizer.c src/lexer/token.c src/lexer/lexer_check_quote.c \
		src/lexer/tokenize_symbol.c src/lexer/lexer.c \
		src/parser/parser.c src/parser/tool.c src/parser/parenthesis.c \
		src/parser/make_tree.c src/parser/insert_tree.c \
		src/parser/check_syntax.c src/parser/match_error.c src/parser/near_token_error.c

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(INC_FILES) $(INC_TYPES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_LIB) $(READLINE_INC)

$(LIBFT):
	@make -C ./libft all

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
