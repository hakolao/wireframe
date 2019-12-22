/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:09:34 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 16:50:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int		main(void)
{
	t_matrix *m1;
	t_matrix *m2;

	m1 = ft_matrix_new(4, 4);
	ft_putstr("m1: ");
	ft_putmatrix(m1);
	m2 = ft_matrix_id(4, 4);
	ft_putstr("m2: ");
	ft_putmatrix(m2);

	t_matrix *m3;
	t_matrix *m4;
	t_matrix *res34 = ft_matrix_new(4, 4);
	double data3[] = {5.50, 3.30, 2.50, 9.11,
					  1.10, 2.20, -3.39, -2.20,
					  5.50, 33.30, 11.51, -21.01,
					  20.02, -20.51, 11.05, -1.91};
	double data4[] = {1.50, 9.30, 2.50, 55.11,
					-1.10, -2.20, 3.39, -12.20,
					18.50, -3.30, -1.54, 19.11,
					770.02, -620.51, 111.05, 21.91};

	m3 = ft_matrix_new(4, 4);
	ft_matrix_set_vals(m3, data3, 16);
	m4 = ft_matrix_new(4, 4);
	ft_matrix_set_vals(m4, data4, 16);
	ft_putstr("\nm3: ");
	ft_putmatrix(m3);
	ft_putstr("m4: ");
	ft_putmatrix(m4);
	ft_putstr("\nres34: ");
	ft_matrix_add(m3, m4, res34);
	ft_putmatrix(res34);

	t_matrix *m5;
	t_matrix *m6;
	t_matrix *res56 = ft_matrix_new(4, 4);
	double data5[] = {15, 11, 14, 2, 3, 6, 7, 9};
	double data6[] = {-2, 2, 4, 22, -25, -3, 33, 11};
	m5 = ft_matrix_new(2, 4);
	ft_matrix_set_vals(m5, data5, 8);
	m6 = ft_matrix_new(4, 2);
	ft_matrix_set_vals(m6, data6, 8);
	ft_putstr("\nm5: ");
	ft_putmatrix(m5);
	ft_putstr("m6: ");
	ft_putmatrix(m6);
	ft_putstr("\nres56: ");
	ft_matrix_mul(m5, m6, res56);
	ft_putmatrix(res56);

	t_matrix *m7;
	t_vector *res71 = ft_vector_new(3);
	double data7[] = {1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12};
	m7 = ft_matrix_new(3, 4);
	ft_matrix_set_vals(m7, data7, 12);
	t_vector *v1;
	v1 = ft_vector_new(3);
	double datav1[] = {-2, 1, 0};
	ft_vector_set_vals(v1, datav1, 3);
	ft_matrix_mul_vector(m7, v1, res71);

	ft_putstr("\nm7: ");
	ft_putmatrix(m7);
	ft_putstr("v1: ");
	ft_putvector(v1);
	ft_putstr("\nres71: ");
	ft_putvector(res71);

	ft_matrix_free(m1);
	ft_matrix_free(m2);
	ft_matrix_free(m3);
	ft_matrix_free(m4);
	ft_matrix_free(res34);
	ft_matrix_free(m5);
	ft_matrix_free(m6);
	ft_matrix_free(res56);
	ft_matrix_free(m7);
	ft_vector_free(v1);
	ft_vector_free(res71);
	return (0);
}
