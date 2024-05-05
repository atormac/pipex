# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:16:39 by atorma            #+#    #+#              #
#    Updated: 2024/04/23 19:15:23 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_toupper.c ft_tolower.c \
		  ft_strlen.c ft_strchr.c ft_strrchr.c \
		  ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
		  ft_strnstr.c ft_atoi.c \
		  ft_memset.c ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c \
		  ft_memmove.c \
		  ft_calloc.c ft_strdup.c \
		  ft_substr.c ft_strjoin.c ft_split.c ft_strtrim.c ft_itoa.c \
		  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		  ft_putendl_fd.c ft_putnbr_fd.c
B_SOURCES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

OBJECTS = $(SOURCES:.c=.o)
B_OBJECTS = $(B_SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

.bonus: $(OBJECTS) $(B_OBJECTS)
	ar rcs $(NAME) $(OBJECTS) $(B_OBJECTS)
	touch .bonus

bonus: .bonus

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) $(B_OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f .bonus

re: fclean all

.PHONY: all bonus clean fclean re
