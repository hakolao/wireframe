# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:09:18 by ohakola           #+#    #+#              #
#    Updated: 2020/01/18 17:09:05 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
NAME = libmatrix.a
DIR_SRC = ./
DIR_OBJ = temp
SOURCES = ft_matrix_new.c \
			ft_matrix_add.c \
			ft_matrix_sub.c \
			ft_matrix_mul.c \
			ft_matrix_id.c \
			ft_matrix_set_all.c \
			ft_scale_matrix.c \
			ft_matrix_scale.c \
			ft_matrix_set_vals.c \
			ft_dimensions_equal.c \
			ft_matrix_add_double.c \
			ft_matrix_sub_double.c \
			ft_matrix_mul_double.c \
			ft_matrix_mul_vector.c \
			ft_putint_fd.c \
			ft_putint.c \
			ft_puterror.c \
			ft_putstr_fd.c \
			ft_putstr.c \
			ft_strlen.c \
			ft_matrix_free.c \
			ft_vector_free.c \
			ft_vector_new.c \
			ft_vector4_new.c \
			ft_vector_scale.c \
			ft_vector_set_all.c \
			ft_vector_set_vals.c \
			ft_vector_to_matrix.c \
			ft_putvector.c \
			ft_vector_mag.c \
			ft_vector_sub.c \
			ft_vector_add.c \
			ft_vector_dot.c \
			ft_vector_cross.c \
			ft_vector_normalize.c \
			ft_view_matrix.c \
			ft_projection_matrix.c \
			ft_vector_forward.c \
			ft_rotation_matrix.c \
			ft_matrix_inverse_4x4.c \
			ft_putmatrix.c
SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
HEADERS = ./
FLAGS = -Wall -Wextra -Werror

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(DIR_OBJ):
	@mkdir -p temp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADERS)/libmatrix.h
	@$(CC) $(FLAGS) -I $(HEADERS) -c -o $@ $<

test:
	@make -C ./
	@$(CC) $(FLAGS) -o test test.c $(OBJS)
	./test
	@/bin/rm test
	@make fclean

clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, re
