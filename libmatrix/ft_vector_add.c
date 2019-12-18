/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:21:09 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 18:04:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

t_vector	*ft_vector_add(t_vector *v1, t_vector *v2)
{
	size_t		i;
	t_vector	*res;

	if (!v1 || !v2 ||
		!(v1->size == v2->size) ||
		(res = ft_vector_new(v1->size)) == NULL)
		return (NULL);
	i = 0;
	while (i < v1->size)
	{
		res->v[i] = v1->v[i] + v2->v[i];
		i++;
	}
	return (res);
}
