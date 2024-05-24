# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 17:55:45 by atorma            #+#    #+#              #
#    Updated: 2024/05/24 14:29:40 by atorma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
MANDATORYDIR = mandatory
BONUSDIR = bonus
SOURCES = main.c pipex.c pipe.c path.c utils.c exit_error.c
B_SOURCES = main_bonus.c pipex_bonus.c pipe_bonus.c path_bonus.c \
			utils_bonus.c exit_error_bonus.c
OBJECTS = $(addprefix $(MANDATORYDIR)/,$(SOURCES:.c=.o))
B_OBJECTS = $(addprefix $(BONUSDIR)/,$(B_SOURCES:.c=.o))
LIBDIR = ./libft


all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ ./libft/libft.a

$(MANDATORYDIR)/%.o: %.c
	$(CC) -I$(MANDATORYDIR) -c $(CFLAGS) $< -o $@

$(BONUSDIR)/%.o: %.c
	$(CC) -I$(BONUSDIR) -c $(CFLAGS) $< -o $@

.bonus: $(B_OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o pipex $(CFLAGS) $^ ./libft/libft.a
	touch .bonus

bonus: .bonus

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS)
	rm -f $(B_OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f .bonus

re: fclean all

.PHONY: all bonus clean fclean re
