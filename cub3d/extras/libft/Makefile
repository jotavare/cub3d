# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 00:18:41 by jotavare          #+#    #+#              #
#    Updated: 2023/11/02 00:44:41 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

HEADERS	=	libft.h
INCLUDE	=	-I .

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_char_in_set.c \
			ft_isdigit.c \
			ft_memcpy.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strnchr.c \
			ft_strncmp.c \
			ft_strndup.c \
			ft_strtrim.c \
			get_next_line.c \

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

all : $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJS)
	rm -f libft.a

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
