/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:57:49 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 16:34:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void		ft_putvector(t_vector *vec)
{
	t_matrix *m;

	if ((m = ft_matrix_new(1, vec->size)) == NULL ||
		ft_vector_to_matrix(vec, m) == 0)
	{
		ft_puterror("Failed to print vector in ft_putvector.\n");
		return ;
	}
	ft_putmatrix(m);
	ft_matrix_free(m);
}
