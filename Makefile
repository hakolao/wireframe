# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2020/01/14 14:15:47 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
NAME = fdf
LIBFT = ./libft
LIBMATRIX = ./libmatrix
DIR_SRC = src
DIR_OBJ = temp
HEADERS = incl
FLAGS = -Wall -Wextra -Werror
LIBMLXFLAGS = -L /usr/local/lib -lmlx -I/usr/local/X11/include -L/usr/X11/lib \
				-lX11 -lXext -framework OpenGL -framework Appkit
LIBMATRIXFLAGS = -L $(LIBMATRIX) -lmatrix
LIBFTFLAGS = -L $(LIBFT) -lft
SOURCES = main.c \
			input.c \
			log.c \
			events.c \
			scene.c \
			line.c \
			draw.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

home: $(DIR_OBJ) $(NAME)HOME

$(NAME): $(OBJS)
	@make -C ./libft
	@make -C ./libmatrix
	$(CC) $(FLAGS) -L $(LIBFT) -lft -L $(LIBMATRIX) -lmatrix -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $@ $^

$(NAME)HOME:
	@make -C ./libft
	@make -C ./libmatrix
	$(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMATRIXFLAGS) $(LIBMLXFLAGS) -o $@ $^

$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMATRIX) clean
	@/bin/rm -rf $(DIR_OBJ)
	
fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean
	@make -C ./libmatrix/ fclean

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
