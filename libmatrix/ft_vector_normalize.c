/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:43:02 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 14:11:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vector	*ft_vector_normalize(t_vector *vec)
{
	t_vector	*new;
	size_t		i;
	double		mag;

	if ((new = ft_vector_new(vec->size)) == NULL)
		return (NULL);
	i = 0;
	mag = ft_vector_mag(vec);
	while (i < vec->size)
	{
		new->v[i] = vec->v[i] / mag;
		i++;
	}
	return (new);
}
