/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:57:49 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 17:59:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void		ft_putvector(t_vector *vec)
{
	t_matrix *m;

	m = ft_vector_to_matrix(vec);
	ft_putmatrix(m);
}
