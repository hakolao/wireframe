/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:28:43 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 17:02:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vector	*ft_matrix_mul_vector(const t_matrix *m1, const t_vector *v)
{
	t_matrix	*new;
	t_matrix	*res_mat;
	t_vector	*res;
	size_t		i;

	if (m1->cols != v->size || ((new = ft_matrix_new(1, m1->rows)) == NULL))
	{
		ft_puterror("Invalid matrix in matrix vector multiplcation\n");
		return (NULL);
	}
	if ((res_mat = ft_matrix_mul(m1, ft_vector_to_matrix(v))) == NULL)
		return (NULL);
	ft_matrix_free(new);
	if ((res = ft_vector_new(m1->rows)) == NULL)
		return (NULL);
	i = 0;
	while (i < m1->rows)
	{
		res->v[i] = VALUE_AT(m1, i, 0);
		i++;
	}
	return (res);
}
