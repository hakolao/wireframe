/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:13:05 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 16:56:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix *ft_matrix_id(size_t cols, size_t rows)
{
	t_matrix 	*m;
	size_t		r;
	size_t		c;

	if (cols != rows || (m = ft_matrix_new(cols, rows)) == NULL)
		return (NULL);
	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < cols)
		{
			VALUE_AT(m, r, c) = 1;
			r++;
			c++;
		}
		r++;
	}
	return (m);
}