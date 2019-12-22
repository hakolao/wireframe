/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:20:30 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 16:44:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

int		ft_vector_forward(t_vector *position, t_vector *target, t_vector *res)
{
	t_vector	*forward_unnormalized;

	if (position->size != target->size || position->size != res->size ||
		(forward_unnormalized = ft_vector_new(position->size)) == NULL ||
		ft_vector_sub(target, position, forward_unnormalized) == 0 ||
		ft_vector_normalize(forward_unnormalized, res) == 0)
	{
		ft_puterror("Invalid input in ft_vector_forward.\n");
		return (0);
	}
	ft_vector_free(forward_unnormalized);
	return (1);
}
