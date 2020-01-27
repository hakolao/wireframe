# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2020/01/27 18:24:35 by ohakola          ###   ########.fr        #
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
			map/map.c \
			map/reset.c \
			map/utils.c \
			camera/camera.c \
			camera/utils.c \
			line/draw.c \
			line/gradient.c \
			scene/axes.c \
			scene/map.c \
			scene/scene.c \
			events/keys.c \
			events/mouse.c \
			events/loop.c \
			ui/ui.c \
			ui/utils.c \
			log.c \
			draw.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@make -C ./libmatrix
	$(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMATRIXFLAGS) -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $@ $^
	# $(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMATRIXFLAGS) $(LIBMLXFLAGS) -o $@ $^

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/map
	@mkdir -p temp/camera
	@mkdir -p temp/line
	@mkdir -p temp/scene
	@mkdir -p temp/ui
	@mkdir -p temp/events

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

.PHONY: all, $(DIR_OBJ), clean, fclean
