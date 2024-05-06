# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 17:55:45 by atorma            #+#    #+#              #
#    Updated: 2024/05/06 20:18:28 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SOURCES = pipex.c path.c utils.c
OBJECTS = $(SOURCES:.c=.o)
LIBDIR = ./libft

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $(NAME) $(CFLAGS) $? ./libft/libft.a

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
