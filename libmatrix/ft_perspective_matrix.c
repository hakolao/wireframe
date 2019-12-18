/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perspective_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:59:32 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 16:14:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_matrix	*ft_orthographic_matrix(t_canvas *c)
{
	t_matrix	*m;

	if ((m = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(m, 0, 0) = 2 / c->width;
	VALUE_AT(m, 1, 1) = 2 / c->height;
	VALUE_AT(m, 2, 2) = 1 / (c->far - c->near);
	VALUE_AT(m, 2, 3) = -c->near / (c->far - c->near);
	VALUE_AT(m, 3, 3) = 1;
	return (m);
}

t_matrix	*ft_perspective_matrix(t_canvas *c)
{
	t_matrix	*m;
	double		ar;

	if ((m = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	ar = c->width / c->height;
	VALUE_AT(m, 0, 0) = 1 / (ar * tan(c->angle / 2));
	VALUE_AT(m, 1, 1) = 1 / tan(c->angle / 2);
	VALUE_AT(m, 2, 2) = (-c->near - c->far) / (c->near - c->far);
	VALUE_AT(m, 3, 2) = 1;
	VALUE_AT(m, 2, 3) = 2 * c->near * c->far / (c->near - c->far);
	return (m);
}
