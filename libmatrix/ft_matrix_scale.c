/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:28:17 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 15:57:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_matrix_scale(size_t cols, size_t rows, double scale)
{
	t_matrix	*m;
	size_t		r;
	size_t		c;

	if (cols != rows || (m = ft_matrix_new(cols, rows)) == NULL)
	{
		ft_puterror("Invalid input in ft_matrix_scale.\n");
		return (NULL);
	}
	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < cols)
		{
			VALUE_AT(m, r, c) = scale;
			r++;
			c++;
		}
		r++;
	}
	return (m);
}
