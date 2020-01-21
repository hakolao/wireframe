/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul_vector_lst.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:24:25 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/21 14:25:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int		ft_matrix_mul_vector_lst(t_matrix *m, t_vector **vecs, size_t n)
{
	size_t		i;
	t_vector	*vec;

	i = 0;
	while (i < n)
	{
		if ((vec = ft_vector4_new(0, 0, 0)) == NULL ||
			ft_matrix_mul_vector(m, vecs[i], vec) == FALSE)
			return (0);
		vec->v[3] = 1;
		ft_vector_free(vecs[i]);
		vecs[i] = vec;
		i++;
	}
	return (1);
}
