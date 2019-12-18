/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_set_vals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:03:48 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:03:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_matrix_set_vals(t_matrix *mat, double *arr, size_t arr_size)
{
	size_t	r;
	size_t	c;
	size_t	len;

	len = mat->cols * mat->rows;
	if (arr_size != len)
	{
		ft_puterror("Invalid array passed (size)\n");
		return;
	}
	r = 0;
	while (r < mat->rows)
	{
		c = 0;
		while (c < mat->cols)
		{
			VALUE_AT(mat, r, c) = arr[c * (mat)->rows + r];
			c++;
		}
		r++;
	}
}
