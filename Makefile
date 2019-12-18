# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2019/12/18 17:17:24 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


C = clang
NAME = fdf
LIBFT = ./libft
LIBMATRIX = ./libmatrix
DIR_SRC = src
DIR_OBJ = temp
HEADERS = incl
FLAGS = -Wall -Wextra -Werror
SOURCES = main.c \
			input.c \
			log.c \
			events.c \
			scene.c \
			draw.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@make -C ./libmatrix
	$(CC) $(FLAGS) -L $(LIBFT) -lft -L $(LIBMATRIX) -lmatrix -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $@ $^
	
$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMATRIX) clean
	@/bin/rm -rf $(DIR_OBJ)
	
fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft/ fclean
	@make -C ./libmatrix/ fclean

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
