/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:09:26 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 16:56:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_matrix_add(const t_matrix *m1, const t_matrix *m2)
{
	size_t			r;
	size_t			c;
	t_matrix		*new;

	if (!m1 || !m2 || !ft_dimensions_equal(m1, m2))
	{
		ft_puterror("Invalid dimensions or inputs given.\n");
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
			VALUE_AT(new, r, c) = VALUE_AT(m1, r, c) + VALUE_AT(m2, r, c);
			c++;
		}
		r++;
	}
	return (new);
}
