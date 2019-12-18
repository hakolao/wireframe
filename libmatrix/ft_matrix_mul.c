/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:09:19 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:18:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_matrix_mul(const t_matrix *m1, const t_matrix *m2)
{
	t_matrix	*new;
	size_t		r;
	size_t		c;
	size_t		i;
	double 		sum;

	if (!(m1->cols == m2->rows || m1->rows == m2->cols) ||
		(new = ft_matrix_new(m1->rows, m2->cols)) == NULL)
	{
		ft_puterror("Invalid rows or columns for matrix multiplication... or malloc err\n");
		return (NULL);
	}
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		while (c < m2->cols)
		{
			sum = 0;
			i = 0;
			while (i < m1->cols)
			{
				sum += VALUE_AT(m1, r, i) * VALUE_AT(m2, i, c);
				i++;
			}
			VALUE_AT(new, r, c) = sum;
			c++;
		}
		r++;
	}
	return (new);
}
