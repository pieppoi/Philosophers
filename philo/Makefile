# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 03:32:23 by mkazuhik          #+#    #+#              #
#    Updated: 2025/10/09 02:00:09 by mkazuhik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = srcs
SRCS = 	$(SRCDIR)/main.c \
		$(SRCDIR)/main_utils.c \
		$(SRCDIR)/monitor.c \
		$(SRCDIR)/parse.c \
		$(SRCDIR)/parse_utils.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/philosopher.c \
		$(SRCDIR)/stagger.c \
		$(SRCDIR)/eat.c \
		$(SRCDIR)/check.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/time_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
