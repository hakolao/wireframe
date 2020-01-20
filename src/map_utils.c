/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:36:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/18 17:41:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		apply_matrix_on_map(t_matrix *m, t_map *map)
{
	size_t		i;
	t_vector	*vec;

	i = 0;
	while (i < map->vertex_count)
	{
		if ((vec = ft_vector4_new(0, 0, 0)) == NULL ||
			ft_matrix_mul_vector(m, map->vertices[i], vec) == 0)
			return (0);
		vec->v[3] = 1;
		ft_vector_free(map->vertices[i]);
		map->vertices[i] = vec;
		i++;
	}
	return (1);
}

int		rotate_map(t_map *map, int amount_x, int amount_y, int amount_z)
{
	t_matrix 	*rotation;
	t_matrix 	*map_rotation;

	map->rot_x += amount_x;
	map->rot_y += amount_y;
	map->rot_z += amount_z;
	
	if ((map_rotation = ft_matrix_new(4, 4)) == NULL ||
		(rotation = ft_rotation_matrix(amount_x, amount_y, amount_z)) == NULL ||
		apply_matrix_on_map(rotation, map) == 0 ||
		ft_matrix_mul(map->rotation, rotation, map_rotation) == 0)
	{
		map->rot_x -= amount_x;
		map->rot_y -= amount_y;
		map->rot_z -= amount_z;
		return (0);
	}
	ft_matrix_free(rotation);
	ft_matrix_free(map->rotation);
	map->rotation = map_rotation;
	return (1);
}

int		scale_map_z(t_map *map, double amount)
{
	t_vector	*scale;
	t_matrix	*scale_m;
	t_matrix	*reset_rotation;

	if ((scale = ft_vector4_new(1, 1, amount)) == NULL ||
		(scale_m = ft_scale_matrix(4, 4, scale)) == NULL ||
		(reset_rotation = ft_matrix_inverse_4x4(map->rotation)) == NULL ||
		apply_matrix_on_map(reset_rotation, map) == 0 ||
		apply_matrix_on_map(scale_m, map) == 0 ||
		apply_matrix_on_map(map->rotation, map) == 0)
		return (0);
	ft_vector_free(scale);
	ft_matrix_free(scale_m);
	ft_matrix_free(reset_rotation);
	return (1);
}
