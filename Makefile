# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 15:58:30 by ohakola           #+#    #+#              #
#    Updated: 2020/02/03 14:44:24 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fdf
LIBFT = ./lib/libft
LIBMATRIX = ./lib/libmatrix
LIBMLX = ./lib/libmlx
DIR_SRC = src
DIR_OBJ = temp
HEADERS = incl
FLAGS = -Wall -Wextra -Werror -O2
LIBMLXFLAGS = -I$(LIBMLX) -L$(LIBMLX) -lmlx -framework OpenGL -framework Appkit
LIBMATRIXFLAGS = -L$(LIBMATRIX) -lmatrix
LIBFTFLAGS = -L$(LIBFT) -lft
SOURCES = main.c \
			map/draw.c \
			map/read.c \
			map/read_utils.c \
			map/utils.c \
			map/gradient.c \
			camera/camera.c \
			camera/utils.c \
			scene.c \
			events/keys.c \
			events/mouse.c \
			events/loop.c \
			events/exit.c \
			ui/ui.c \
			ui/utils.c \
			ui/guide.c \
			log.c \
			draw.c \
			line.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(LIBMATRIX)
	@make -C $(LIBMLX)
	$(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMATRIXFLAGS) $(LIBMLXFLAGS) -o $@ $^

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/map
	@mkdir -p temp/camera
	@mkdir -p temp/draw
	@mkdir -p temp/ui
	@mkdir -p temp/events

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/$(NAME).h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMATRIX) clean
	@make -C $(LIBMLX) clean
	@/bin/rm -rf $(DIR_OBJ)
	
fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(LIBMATRIX) fclean
	@make -C $(LIBMLX) fclean

norm:
	norminette $(HEADERS) $(LIBFT) $(LIBMATRIX) $(DIR_SRC)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, norm
