# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thugo <thugo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/18 15:00:09 by thugo             #+#    #+#              #
#    Updated: 2017/11/01 03:24:53 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Binary
NAME = minishell

#Flags
FLAGS = -Werror -Wextra -Wall

#Sources
SRC = main.c env.c envaccess.c prompt.c promptgit.c parser.c exec.c \
	  builtin.c stats.c signal.c cwd.c

#Builtins
BUILTINS = exit.c cd.c env.c setenv.c unsetenv.c

#Debug
DEBUG = 2

SRC += $(addprefix builtins/, $(BUILTINS))
OBJ = $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\n"
	@make -C libft
	@printf "[\e[33m$(NAME)\e[0m] \e[34mBuild:\e[0m $(NAME)"
ifeq ($(DEBUG), 1)
	@gcc -Llibft -lft -o $(NAME) $(OBJ)
	@printf " [\e[32mOK\e[0m][\e[33mDEBUG MODE\e[0m]\n"
else ifeq ($(DEBUG), 2)
	@gcc -fsanitize=address -Llibft -lft -o $(NAME) $(OBJ)
	@printf " [\e[32mOK\e[0m][\e[33mDEBUG MODE\e[0m]\n"
else
	@gcc -Llibft -lft -o $(NAME) $(OBJ)
	@printf " [\e[32mOK\e[0m]\n"
endif

obj/%.o: src/%.c
	@printf "[\e[33m$(NAME)\e[0m] \e[34mCompile:\e[0m $^\e[K\r"
	@mkdir -p $(dir $@)
ifeq ($(DEBUG), 1)
	@gcc -g -I include -I libft -c $^ -o $@
else ifeq ($(DEBUG), 2)
	@gcc -g -fsanitize=address -I include -I libft -c $^ -o $@
else
	@gcc $(FLAGS) -I include -I libft -c $^ -o $@
endif
	@printf "[\e[33m$(NAME)\e[0m] \e[34mCompile:\e[0m $^ [\e[32mOK\e[0m]\e[K\r"

clean:
	@make -C libft clean
	@printf "[\e[33m$(NAME)\e[0m] \e[34mDelete objects\e[0m"
	@rm -f $(OBJ)
	@rm -rf obj
	@printf " [\e[32mOK\e[0m]\n"

fclean: clean
	@make -C libft fclean
	@printf "[\e[33m$(NAME)\e[0m] \e[34mDelete binary\e[0m"
	@rm -f $(NAME)
	@printf " [\e[32mOK\e[0m]\n"

re: fclean all

run: all
	@printf "[\e[33m$(NAME)\e[0m] \e[34mRun binary\e[0m\n"
	@./$(NAME)

.PHONY: all clean fclean re run
