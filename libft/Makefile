# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 14:17:52 by jiwonhan          #+#    #+#              #
#    Updated: 2022/12/29 19:44:09 by hyuncpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAG = -Wall -Wextra -Werror -c
AR = ar rc
RM = rm -f

HEADER = libft.h
SRC = ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isalnum.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BNS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ = $(SRC:%.c=%.o)
BNS_OBJ = $(BNS_SRC:%.c=%.o)
ifdef LINK_BONUS
	OBJ_FILES = $(OBJ) $(BNS_OBJ)
else
	OBJ_FILES = $(OBJ)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	@$(AR) $@ $^

%.o : %.c $(HEADER)
	@$(CC) $(CFLAG) $< -o $@ -I .

bonus :
	make LINK_BONUS=1 all

clean : 
	@$(RM) $(OBJ) $(BNS_OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean 
	@$(MAKE)

.PHONY : all bonus clean fclean re
