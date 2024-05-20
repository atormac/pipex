# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 17:55:45 by atorma            #+#    #+#              #
#    Updated: 2024/05/18 18:38:03 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SOURCES = main.c pipex.c pipe.c path.c utils.c exit_error.c
BUILDDIR = mandatory
OBJECTS = $(addprefix $(BUILDDIR)/,$(SOURCES:.c=.o))
LIBDIR = ./libft

$(BUILDDIR)/%.o: %.c
	$(CC) -I$(BUILDDIR) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ ./libft/libft.a

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
