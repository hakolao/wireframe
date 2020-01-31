/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:13:58 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/31 16:37:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Resets map rotation & scale to original values. May
** have some rounding diffrences.
*/

int		reset_map(t_map *map)
{
	if (!ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) ||
		!ft_matrix_mul_vector_lst(map->reset_scale, map->vertices,
			map->vertex_count))
		return (0);
	ft_matrix_free(map->scale);
	if (!ft_rotation_matrix(0, 0, 0, map->rotation) ||
		!ft_matrix_inverse_4x4(map->rotation, map->reset_rotation) ||
		(map->scale = ft_matrix_id(4, 4)) == NULL ||
		!ft_matrix_inverse_4x4(map->scale, map->reset_scale))
		return (0);
	set_map_info(map);
	return (1);
}
