/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:20:30 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 17:56:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vector	*ft_vector_forward(t_vector *position, t_vector *target)
{
	t_vector	*forward;
	t_vector	*forward_unnormalized;

	if ((forward_unnormalized =
		ft_vector_sub(position, target)) == NULL)
		return (NULL);
	forward_unnormalized->v[3] = 1;
	if ((forward =
		ft_vector_normalize(forward_unnormalized)) == NULL)
		return (NULL);
	forward->v[3] = 1;
	return (forward);
}
