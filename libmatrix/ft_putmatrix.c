/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmatrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:41:16 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 16:48:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_putmatrix(t_matrix *mat)
{
	size_t c;
	size_t r;

	r = 0;
	if (!mat)
		return ;
	ft_putstr("Matrix, cols: ");
	ft_putint((int)(mat->cols));
	ft_putstr(" rows: ");
	ft_putint((int)(mat->rows));
	ft_putstr("\n");
	while (r < mat->rows)
	{
		c = 0;
		while (c < mat->cols)
		{
			ft_putdouble(VALUE_AT(mat, r, c));
			if (c < mat->cols - 1)
				ft_putstr(" ");
			c++;
		}
		ft_putstr("\n");
		r++;
	}
}
