/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:43:50 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 16:01:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int		ft_matrix_sub(const t_matrix *m1, const t_matrix *m2, t_matrix *res)
{
	size_t r;
	size_t c;

	if (!m1 || !m2 || !res || !ft_dimensions_equal(m1, m2) ||
		!ft_dimensions_equal(m1, res))
	{
		ft_puterror("Invalid input in ft_matrix_sub.\n");
		return (0);
	}
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		while (c < m1->cols)
		{
			VALUE_AT(res, r, c) = VALUE_AT(m1, r, c) - VALUE_AT(m2, r, c);
			c++;
		}
		r++;
	}
	return (1);
}
