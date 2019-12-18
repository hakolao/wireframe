/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:28:17 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:28:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_matrix_scale(t_matrix *mat, double scale)
{
	int len;
	int i;

	len = mat->cols * mat->rows;
	i = 0;
	while (i < len)
		mat->m[i++] *= scale;
}
