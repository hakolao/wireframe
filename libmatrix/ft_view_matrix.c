/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:56:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/16 16:42:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static t_matrix		*view_matrix(t_vector *xaxis, t_vector *yaxis,
					t_vector *zaxis, t_vector *position)
{
	t_matrix	*view;
	double		vals[16];

	if ((view = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	vals[0] = xaxis->v[0];
	vals[1] = yaxis->v[0];
	vals[2] = zaxis->v[0];
	vals[3] = 0;
	vals[4] = xaxis->v[1];
	vals[5] = yaxis->v[1];
	vals[6] = zaxis->v[1];
	vals[7] = 0;
	vals[8] = xaxis->v[2];
	vals[9] = yaxis->v[2];
	vals[10] = zaxis->v[2];
	vals[11] = 0;
	vals[12] = -ft_vector_dot(xaxis, position);
	vals[13] = -ft_vector_dot(yaxis, position);
	vals[14] = -ft_vector_dot(zaxis, position);
	vals[15] = 1;
	ft_matrix_set_vals(view, vals, 16);
	return (view);
}

t_matrix			*ft_fps_cam(t_vector *position, double pitch, double yaw)
{
	t_vector	*zaxis;
	t_vector	*xaxis;
	t_vector	*yaxis;
	t_matrix	*view;

	pitch *= M_PI / 180;
	yaw *= M_PI / 180;
	if ((zaxis = ft_vector4_new(
		sin(yaw) * cos(pitch), -sin(pitch), cos(pitch) * cos(yaw))) == NULL ||
		(xaxis = ft_vector4_new(cos(yaw), 0, -sin(yaw))) == NULL ||
		(yaxis = ft_vector4_new(
			sin(yaw) * sin(pitch), cos(pitch), cos(yaw) * sin(pitch)))
				== NULL)
		return (NULL);
	xaxis->v[3] = 0;
	yaxis->v[3] = 0;
	zaxis->v[3] = 0;
	if ((view = view_matrix(xaxis, yaxis, zaxis, position)) == NULL)
		return (NULL);
	ft_vector_free(zaxis);
	ft_vector_free(xaxis);
	ft_vector_free(yaxis);
	return (view);
}