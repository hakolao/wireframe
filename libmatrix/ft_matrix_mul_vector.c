/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:28:43 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:16:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_matrix_mul_vector(const t_matrix *m1, const t_vector *v)
{
	t_matrix *new;
	t_matrix *res;

	if (m1->cols != v->size || ((new = ft_matrix_new(1, m1->rows)) == NULL))
	{
		ft_puterror("Invalid matrix in matrix vector multiplcation\n");
		return (NULL);
	}
	if ((res = ft_matrix_mul(m1, ft_vector_to_matrix(v))) == NULL)
		return (NULL);
	ft_matrix_free(new);
	return (res);
}
