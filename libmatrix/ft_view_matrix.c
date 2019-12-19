/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:56:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 16:21:45 by ohakola          ###   ########.fr       */
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

t_matrix			*ft_view_matrix(t_vector *position, t_vector *target,
					t_vector *up)
{
	t_vector	*forward;
	t_vector	*forward_unnormalized;
	t_vector	*sideways;
	t_vector	*v;
	t_matrix	*view;

	if ((forward_unnormalized = ft_vector_sub(position, target)) == NULL)
		return (NULL);
	forward_unnormalized->v[3] = 1;
	if ((forward =
		ft_vector_normalize(forward_unnormalized)) == NULL)
		return (NULL);
	if ((sideways = ft_vector_normalize(ft_vector_cross(forward, up))) == NULL)
		return (NULL);
	if ((v = ft_vector_cross(sideways, forward)) == NULL)
		return (NULL);
	if ((view = view_matrix(sideways, v, forward, position)) == NULL)
		return (NULL);
	ft_vector_free(forward);
	ft_vector_free(forward_unnormalized);
	ft_vector_free(sideways);
	ft_vector_free(v);
	return (view);
}