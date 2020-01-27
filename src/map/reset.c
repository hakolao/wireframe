/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:13:58 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 12:29:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Resets map rotation & scale to original values. May
** have some rounding diffrences.
*/

int		reset_map(t_map *map)
{
	if (ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) == FALSE ||
		ft_matrix_mul_vector_lst(map->reset_scale, map->vertices,
			map->vertex_count) == FALSE)
		return (0);
	ft_matrix_free(map->rotation);
	ft_matrix_free(map->scale);
	ft_matrix_free(map->reset_rotation);
	ft_matrix_free(map->reset_scale);
	if ((map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL ||
		(map->reset_rotation =
			ft_matrix_inverse_4x4(map->rotation)) == NULL ||
		(map->scale = ft_matrix_id(4, 4)) == NULL ||
		(map->reset_scale =
			ft_matrix_inverse_4x4(map->scale)) == NULL)
		return (0);
	set_map_info(map);
	return (1);
}
