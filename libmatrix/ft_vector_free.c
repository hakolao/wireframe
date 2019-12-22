/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:59:53 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 16:16:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_vector_free(t_vector *vec)
{
	if (!vec)
	{
		ft_puterror("Invalid input in ft_vector_free\n.");
		return ;
	}
	free(vec->v);
	free(vec);
}
