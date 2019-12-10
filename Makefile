# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2019/12/10 17:03:17 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


C = clang
NAME = fdf
LIBFT = ./libft
DIR_SRC = src
DIR_OBJ = temp
HEADERS = incl
FLAGS = -Wall -Wextra -Werror
SOURCES = main.c \
			input.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	$(CC) $(FLAGS) -L $(LIBFT) -lft -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $@ $^
	
$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@/bin/rm -rf $(DIR_OBJ)
	
fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
