/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:01 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 13:07:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATRIX_H
# define LIBMATRIX_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_matrix
{
	size_t 	rows;
	size_t 	cols;
	double	*m;
}				t_matrix;

typedef struct 	s_vector
{
	size_t	size;
	double	*v;
}				t_vector;

# define VALUE_AT(mat, r, c) (mat)->m[c * (mat)->rows + r]

t_matrix	*ft_matrix_new(size_t cols, size_t rows);
t_matrix	*ft_matrix_id(size_t cols, size_t rows);
t_matrix	*ft_matrix_add_double(const t_matrix *m1, const double d);
t_matrix	*ft_matrix_add(const t_matrix *m1, const t_matrix *m2);
t_matrix	*ft_matrix_sub_double(const t_matrix *m1, const double d);
t_matrix	*ft_matrix_sub(const t_matrix *m1, const t_matrix *m2);
t_matrix	*ft_matrix_mul(const t_matrix *m1, const t_matrix *m2);
t_matrix	*ft_matrix_mul_double(const t_matrix *m1, const double d);
t_vector	*ft_vector_new(size_t size);
t_vector	*ft_vector4_new(double x, double z, double y);
t_matrix	*ft_vector_to_matrix(const t_vector *vec);
t_matrix	*ft_matrix_mul_vector(const t_matrix *m1, const t_vector *v);
void		ft_matrix_scale(t_matrix *mat, double scale);
void		ft_vector_scale(t_vector *vec, double scale);
void		ft_vector_set_all(t_vector *vec, double d);
void		ft_vector_set_vals(t_vector *vec, double *arr, size_t arr_size);
void		ft_matrix_set_vals(t_matrix *mat, double *arr, size_t arr_size);
int			ft_dimensions_equal(const t_matrix *m1, const t_matrix *m2);
void		ft_putint_fd(int nb, int fd);
void 		ft_putstr_fd(char const *str, int fd);
void 		ft_puterror(char *err);
void		ft_putstr(char const *str);
void		ft_putint(int nb);
size_t		ft_strlen(const char *str);
void		ft_putdouble(double num);
void		ft_putmatrix(t_matrix *mat);
void		ft_matrix_set_all(t_matrix *mat, double nb);
void		ft_matrix_free(t_matrix *mat);
void		ft_vector_free(t_vector *vec);
void		ft_putvector(t_vector *vec);

#endif
