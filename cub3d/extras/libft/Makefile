# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 00:18:41 by jotavare          #+#    #+#              #
#    Updated: 2023/11/04 18:28:57 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags (enables warnings and debugging information).
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

# Executable name, header files, and flags to include header files.
NAME	=	libft.a
HEADERS	=	libft.h
INCLUDE	=	-I .

# Path to source files.
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

# Generate object file names (.c -> .o) from source files.
OBJS	=	$(patsubst %.c,%.o,$(SRCS))

# Makefile rules.
# Build the project.
all : $(NAME)

# Build the Libft executable.
$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

# Build object files from source files.
%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean up object files.
clean :
	rm -f $(OBJS)
	rm -f libft.a

# Remove the executable and clean files.
fclean : clean
	rm -f $(NAME)

# Clean and rebuild the project.
re : fclean all

# Rules that are not associated with files.
.PHONY : all clean fclean re
