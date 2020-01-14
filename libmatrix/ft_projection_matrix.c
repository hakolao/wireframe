/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:59:32 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/14 17:59:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"
#include <stdio.h>

t_matrix	*ft_orthographic_matrix(t_canvas *c)
{
	t_matrix	*m;

	if ((m = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(m, 0, 0) = 1 / c->width;
	VALUE_AT(m, 1, 1) = 1 / c->height;
	VALUE_AT(m, 2, 2) = -2 / (c->far - c->near);
	VALUE_AT(m, 2, 3) = -(c->far + c->near) / (c->far - c->near);
	VALUE_AT(m, 3, 3) = 1;
	return (m);
}

t_matrix	*ft_perspective_matrix(t_canvas *c)
{
	t_matrix	*m;
	double		ar;
	double		angle;

	angle = c->angle * M_PI / 180;
	if (!c || (m = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	ar = c->width / c->height;
	printf("Canvas: far: %f, near: %f, angle: %f, height: %f, width: %f\n",
			c->far, c->near, c->angle, c->height, c->width);
	printf("Ar: %f\n", ar);
	printf("Angle: %f\n", angle);
	VALUE_AT(m, 0, 0) = 1 / (ar * tan(angle / 2));
	VALUE_AT(m, 1, 1) = 1 / tan(angle / 2);
	VALUE_AT(m, 2, 2) = -(c->near + c->far) / (c->far - c->near);
	VALUE_AT(m, 3, 2) = -1;
	VALUE_AT(m, 2, 3) = -2 * c->near * c->far / (c->far - c->near);
	return (m);
}
