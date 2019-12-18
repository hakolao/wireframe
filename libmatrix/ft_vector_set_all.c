/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:38:34 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 17:39:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_vector_set_all(t_vector *vec, double d)
{
	size_t i;

	if (!vec)
		return ;
	i = 0;
	while (i < vec->size)
		vec->v[i++] = d;
}
