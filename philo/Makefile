# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkazuhik <mkazuhik@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 03:32:23 by mkazuhik          #+#    #+#              #
#    Updated: 2025/10/01 05:26:38 by mkazuhik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

# Optional debug build flags (enable with `make DEBUG=1`)
DEBUG ?= 0
ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

# Default run arguments (override with `make run ARGS="3 800 200 200"`)
ARGS ?= 3 800 200 200

# Valgrind command (extend as needed)
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=0

# AddressSanitizer fallback (if Valgrind unusable on host)
SAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -g -O0

SRCDIR = srcs
SRCS = 	$(SRCDIR)/main.c \
		$(SRCDIR)/main_utils.c \
		$(SRCDIR)/monitor.c \
		$(SRCDIR)/parse.c \
		$(SRCDIR)/parse_utils.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/philosopher.c \
		$(SRCDIR)/eat.c \
		$(SRCDIR)/check.c \
		$(SRCDIR)/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME) $(ARGS)

valgrind: $(NAME)
	@command -v valgrind >/dev/null 2>&1 || { \
		echo "valgrind not found. Install it (e.g. sudo apt-get install -y valgrind)"; \
		exit 127; \
	}
	$(VALGRIND) ./$(NAME) $(ARGS)

asan: fclean
	$(CC) $(CFLAGS) $(SAN_FLAGS) -o $(NAME) $(SRCS)
	ASAN_OPTIONS="halt_on_error=0:exitcode=0:detect_leaks=1" ./$(NAME) $(ARGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re run valgrind asan
