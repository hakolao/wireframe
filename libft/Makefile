# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:43:04 by ohakola           #+#    #+#              #
#    Updated: 2019/12/10 13:30:23 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FILES = ft_atoi.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memdel.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_strstr.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isupper.c \
		ft_putchar.c \
		ft_putstr_fd.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_isalpha.c \
		ft_islower.c \
		ft_memalloc.c \
		ft_putchar_fd.c \
		ft_strcmp.c \
		ft_strnstr.c \
		ft_toupper.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strdup.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_itoa_base.c \
		ft_itoa.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strsplit_lst.c \
		ft_lstfold.c \
		ft_lstappend.c \
		ft_realloc.c \
		get_next_line.c \
		ft_isqrt.c \
		ft_sqrt.c \
		ft_strfill.c \
		ft_lstlen.c \
		ft_bzero.c

OBJECTS = 	ft_atoi.o \
			ft_isascii.o \
			ft_isprint.o \
			ft_memdel.o \
			ft_putstr.o \
			ft_strlen.o \
			ft_strstr.o \
			ft_isalnum.o \
			ft_isdigit.o \
			ft_isupper.o \
			ft_putchar.o \
			ft_putstr_fd.o \
			ft_strncmp.o \
			ft_tolower.o \
			ft_isalpha.o \
			ft_islower.o \
			ft_memalloc.o \
			ft_putchar_fd.o \
			ft_strcmp.o \
			ft_strnstr.o \
			ft_toupper.o \
			ft_memcpy.o \
			ft_memccpy.o \
			ft_memset.o \
			ft_memmove.o \
			ft_memchr.o \
			ft_memcmp.o \
			ft_strdup.o \
			ft_strcpy.o \
			ft_strncpy.o \
			ft_strcat.o \
			ft_strncat.o \
			ft_strlcat.o \
			ft_strchr.o \
			ft_strrchr.o \
			ft_putnbr.o \
			ft_putnbr_fd.o \
			ft_itoa_base.o \
			ft_itoa.o \
			ft_putendl.o \
			ft_putendl_fd.o \
			ft_strnew.o \
			ft_strdel.o \
			ft_strclr.o \
			ft_striter.o \
			ft_striteri.o \
			ft_strmap.o \
			ft_strmapi.o \
			ft_strequ.o \
			ft_strnequ.o \
			ft_strsub.o \
			ft_strjoin.o \
			ft_strtrim.o \
			ft_strsplit.o \
			ft_lstnew.o \
			ft_lstdelone.o \
			ft_lstdel.o \
			ft_lstadd.o \
			ft_lstiter.o \
			ft_lstmap.o \
			ft_strsplit_lst.o \
			ft_lstfold.o \
			ft_lstappend.o \
			ft_realloc.o \
			get_next_line.o \
			ft_isqrt.o \
			ft_sqrt.o \
			ft_strfill.o \
			ft_lstlen.o \
			ft_bzero.o

INCLUDES = ./
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(FILES) -I $(INCLUDES)
	ar rc $(NAME) $(OBJECTS)

test: 
	gcc $(FLAGS) -o run_tests $(FILES) tests/test.c -I $(INCLUDES)
	./run_tests
	@/bin/rm -f run_tests

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
