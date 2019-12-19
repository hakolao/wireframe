/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:28:43 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 15:03:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vector	*ft_matrix_mul_vector(const t_matrix *m1, const t_vector *v)
{
	t_vector	*res;
	size_t		r;
	size_t		c;

	if (m1->cols != v->size)
	{
		ft_puterror("Invalid matrix in matrix vector multiplcation\n");
		return (NULL);
	}
	if ((res = ft_vector_new(m1->rows)) == NULL)
		return (NULL);
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		while (c < m1->cols)
		{
			res->v[c] += VALUE_AT(m1, r, c) * v->v[c];
			c++;
		}
		r++;
	}
	return (res);
}
