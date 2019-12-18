/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:27:39 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 17:15:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

double		ft_vector_dot(t_vector *v1, t_vector *v2)
{
	size_t		i;
	double		res;

	if (!v1 || !v2 || !(v1->size == v2->size))
	{
		ft_puterror("Invalid vector sizes for dot product\n");
		return (0);
	}
	i = 0;
	res = 0;
	while (i < v1->size)
	{
		res += v1->v[i] * v2->v[i];
		i++;
	}
	return (res);
}
