/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:27:38 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 18:27:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_vector_scale(t_vector *vec, double scale)
{
	size_t i;

	if (!vec)
		return ;
	i = 0;
	while (i < vec->size)
		vec->v[i++] *= scale;
}
