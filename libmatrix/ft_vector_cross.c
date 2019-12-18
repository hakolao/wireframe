/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_cross.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:30:13 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 14:45:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

/*
** x = Ay * Bz - By * Az = 0
** y = Az * Bx - Bz * Ax = 0
** z = Ax * By - Bx * Ay = -1
*/

t_vector	*ft_vector_cross(t_vector *v1, t_vector *v2)
{
	t_vector	*res;

	if (!v1 || !v2 ||
		!(v1->size == v2->size) ||
		(res = ft_vector_new(v1->size)) == NULL)
		return (NULL);
	res->v[0] = v1->v[1] * v2->v[2] - v2->v[1] * v1->v[2];
	res->v[1] = v1->v[2] * v2->v[0] - v2->v[2] * v1->v[0];
	res->v[2] = v1->v[0] * v2->v[1] - v2->v[0] * v1->v[1];
	return (res);
}
