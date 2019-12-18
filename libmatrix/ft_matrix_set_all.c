/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_set_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:22:18 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 17:38:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_matrix_set_all(t_matrix *mat, double nb)
{
	int len;
	int i;

	len = mat->cols * mat->rows;
	i = 0;
	while (i < len)
		mat->m[i++] = nb;
}
