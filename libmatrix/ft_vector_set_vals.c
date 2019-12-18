/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set_vals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:40:55 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:21:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void		ft_vector_set_vals(t_vector *vec, double *arr, size_t arr_size)
{
	size_t i;

	if (arr_size != vec->size)
	{
		ft_puterror("Invalid array passed (size)\n");
		return;
	}
	i = 0;
	while (i < vec->size)
	{
		vec->v[i] = arr[i];
		i++;
	}
}
