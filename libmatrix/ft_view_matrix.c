/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:56:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/16 12:30:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static t_matrix		*view_matrix(t_vector *sideways, t_vector *v,
					t_vector *forward, t_vector *position)
{
	t_matrix	*view;
	double		vals[16];

	if ((view = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	vals[0] = sideways->v[0];
	vals[1] = v->v[0];
	vals[2] = forward->v[0];
	vals[3] = 0;
	vals[4] = sideways->v[1];
	vals[5] = v->v[1];
	vals[6] = forward->v[1];
	vals[7] = 0;
	vals[8] = sideways->v[2];
	vals[9] = v->v[2];
	vals[10] = forward->v[2];
	vals[11] = 0;
	vals[12] = -ft_vector_dot(sideways, position);
	vals[13] = -ft_vector_dot(v, position);
	vals[14] = -ft_vector_dot(forward, position);
	vals[15] = 1;
	ft_matrix_set_vals(view, vals, 16);
	return (view);
}

t_matrix			*ft_look_at(t_vector *position, t_vector *target,
					t_vector *up)
{
	t_vector	*forward;
	t_vector	*sideways;
	t_vector	*cross_forward_up;
	t_vector	*v;
	t_matrix	*view;

	if ((cross_forward_up = ft_vector_new(position->size)) == NULL ||
		(sideways = ft_vector_new(position->size)) == NULL ||
		(v = ft_vector_new(position->size)) == NULL ||
		(forward = ft_vector_new(position->size)) == NULL ||
		ft_vector_forward(position, target, forward) == 0 ||
		ft_vector_cross(forward, up, cross_forward_up) == 0 ||
		ft_vector_normalize(cross_forward_up, sideways) == 0 ||
		ft_vector_cross(sideways, forward, v) == 0 ||
		(view = view_matrix(sideways, v, forward, position)) == NULL)
	{
		ft_puterror("Invalid input or smth went wrong in ft_view_matrix.\n");
		return (NULL);
	}
	ft_vector_free(forward);
	ft_vector_free(sideways);
	ft_vector_free(cross_forward_up);
	ft_vector_free(v);
	return (view);
}

t_matrix			*ft_fps_cam(t_vector *position, double pitch, double yaw)
{
	t_vector	*forward;
	t_vector	*sideways;
	t_vector	*v;
	t_matrix	*view;

	pitch *= M_PI / 180;
	yaw *= M_PI / 180;
	if ((forward = ft_vector4_new(
		sin(yaw) * cos(pitch), -sin(pitch), cos(pitch) * cos(yaw))) == NULL ||
		(sideways = ft_vector4_new(cos(yaw), 0, -sin(yaw))) == NULL ||
		(v = ft_vector4_new(
			sin(yaw) * sin(pitch), cos(pitch), cos(yaw) * sin(pitch)))
				== NULL ||
		(view = view_matrix(sideways, v, forward, position)) == NULL)
		return (NULL);
	ft_vector_free(forward);
	ft_vector_free(sideways);
	ft_vector_free(v);
	return (view);
}