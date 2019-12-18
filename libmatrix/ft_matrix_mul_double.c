/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_mul_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:22:56 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 16:56:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix 	*ft_matrix_mul_double(const t_matrix *m1, const double d)
{
	size_t		r;
	size_t		c;
	t_matrix	*new;

	if (!m1)
	{
		ft_puterror("Invalid input m1 given.\n");
		return (NULL);
	}
	if ((new = ft_matrix_new(m1->cols, m1->rows)) == NULL)
		return (NULL);
	r = 0;
	while (r < m1->rows)
	{
		c = 0;
		while (c < m1->cols)
		{
			VALUE_AT(new, r, c) = VALUE_AT(m1, r, c) * d;
			c++;
		}
		r++;
	}
	return (new);
}
