# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmunier <nmunier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 13:34:19 by nmunier           #+#    #+#              #
#    Updated: 2025/04/01 19:00:40 by nmunier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

CC = cc
CFLAGS = -Werror -Wall -Wextra -g3
NAME = philo
LIB_NAME = $(NAME).a

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# Directories

PROJECT_DIR = project
THREAD_DIR = $(PROJECT_DIR)/threads
CHECKER_DIR = $(PROJECT_DIR)/checker

# Files

MAIN_FILE = $(PROJECT_DIR)/philo.c
THREAD_FILES = $(THREAD_DIR)/utils.c \
			   $(THREAD_DIR)/utils2.c \
			   $(THREAD_DIR)/philo_utils.c \
			   $(THREAD_DIR)/philo_utils2.c \
			   $(THREAD_DIR)/table_utils.c \
			   $(THREAD_DIR)/routine.c \
			   $(THREAD_DIR)/philosophers.c \
			   $(THREAD_DIR)/table.c
CHECKER_FILES = $(CHECKER_DIR)/input_checker.c \
				$(CHECKER_DIR)/ft_atoi.c

# File Group

MAIN_FILE = $(PROJECT_DIR)/$(NAME).c

MANDATORY_FILES = $(THREAD_FILES) $(CHECKER_FILES)

OBJECTS = $(MANDATORY_FILES:.c=.o)

# Header

HEADERS = -I $(PROJECT_DIR)/headers -I $(PROJECT_DIR)/struct

# Making

%.o: %.c
	@echo "$(RED)Compiling: $(DEF_COLOR)$(YELLOW)" $< "$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

all : $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(LIB_NAME) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(MAIN_FILE) $(LIB_NAME) $(HEADERS)
	@echo "$(BLUE)╔════════════════════════════════════════╗$(DEF_COLOR)"
	@echo "$(BLUE)║$(DEF_COLOR)$(GREEN)    philosophers executable created!    $(DEF_COLOR)$(BLUE)║$(DEF_COLOR)"
	@echo "$(BLUE)╚════════════════════════════════════════╝$(DEF_COLOR)"

clean:
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)
	@echo "$(BLUE)philo has been cleaned from object files!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_NAME)
	@echo "$(BLUE)philo has been cleaned the library file and the executable!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re
