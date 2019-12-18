/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_to_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:43:33 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:13:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_vector_to_matrix(const t_vector *vec)
{
	t_matrix	*new;

	if ((new = ft_matrix_new(1, vec->size)) == NULL)
		return (NULL);
	new->cols = 1;
	new->rows = vec->size;
	ft_matrix_set_vals(new, vec->v, vec->size);
	return (new);
}
