/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:36:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 16:26:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Set's vertex limits for map information
*/

static void		set_vertex_limits(t_map *map, t_vector *vertex)
{
	map->x_max = map->x_max >= vertex->v[0] ? map->x_max : vertex->v[0];
	map->x_min = map->x_min <= vertex->v[0] ? map->x_min : vertex->v[0];
	map->y_max = map->y_max >= vertex->v[1] ? map->y_max : vertex->v[1];
	map->y_min = map->y_min <= vertex->v[1] ? map->y_min : vertex->v[1];
	map->z_max = map->z_max >= vertex->v[2] ? map->z_max : vertex->v[2];
	map->z_min = map->z_min <= vertex->v[2] ? map->z_min : vertex->v[2];
	map->z = map->z_max - map->z_min;
}

/*
** Sets map information. This is used after map data has been
** manipulated.
*/

int				set_map_info(t_map *map)
{
	size_t	i;

	i = 0;
	map->x_max = 0;
	map->x_min = 0;
	map->y_max = 0;
	map->y_min = 0;
	map->z_max = 0;
	map->z_min = 0;
	while (i < map->vertex_count)
		set_vertex_limits(map, map->vertices[i++]);
	return (0);
}

/*
** Tranforms map from read linked list into array of vertices, in addition
** it shifts map's pivot to it's center in 0, 0, 0.
*/

int				shift_map_vertices(t_map *map)
{
	t_vector	*shift;
	size_t		i;

	if (!(shift =
			  ft_vector4_new(-map->x_max / 2, -map->y_max / 2, -z_shift(map))))
		return (0);
	i = 0;
	while (i < map->vertex_count)
	{
		if (!ft_vector_add(map->vertices[i], shift, map->vertices[i]))
			return (0);
		map->vertices[i++]->v[3] = 1;
	}
	ft_vector_free(shift);
	set_map_info(map);
	return (1);
}

/*
** Rotates map by given x, y, z angles
*/

int				rotate_map(t_map *map, int amount_x, int amount_y, int amount_z)
{
	t_matrix	*rotation;
	t_matrix	*map_rotation;
	t_matrix	*reset_rotation;

	if ((map_rotation = ft_matrix_new(4, 4)) == NULL ||
		(rotation = ft_rotation_matrix(amount_x, amount_y, amount_z)) == NULL ||
		ft_matrix_mul(rotation, map->rotation, map_rotation) == FALSE ||
		ft_matrix_mul_vector_lst(rotation, map->vertices,
			map->vertex_count) == FALSE ||
		(reset_rotation = ft_matrix_inverse_4x4(map_rotation)) == NULL)
		return (0);
	ft_matrix_free(rotation);
	ft_matrix_free(map->rotation);
	ft_matrix_free(map->reset_rotation);
	map->rotation = map_rotation;
	map->reset_rotation = reset_rotation;
	return (1);
}

/*
** Scales map by given x y z scale amounts
*/

int				scale_map(t_map *map, double x, double y, double z)
{
	t_vector	*scale;
	t_matrix	*scale_m;
	t_matrix	*map_scale;
	t_matrix	*reset_scale;

	if ((map_scale = ft_matrix_new(4, 4)) == NULL ||
		(scale = ft_vector4_new(x, y, z)) == NULL ||
		(scale_m = ft_scale_matrix(4, 4, scale)) == NULL ||
		ft_matrix_mul(map->scale, scale_m, map_scale) == FALSE ||
		(reset_scale = ft_matrix_inverse_4x4(map_scale)) == NULL ||
		ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) == FALSE ||
		ft_matrix_mul_vector_lst(scale_m, map->vertices,
			map->vertex_count) == FALSE ||
		set_map_info(map) ||
		ft_matrix_mul_vector_lst(map->rotation, map->vertices,
			map->vertex_count) == FALSE)
		return (0);
	ft_matrix_free(map->scale);
	ft_matrix_free(map->reset_scale);
	ft_vector_free(scale);
	ft_matrix_free(scale_m);
	map->scale = map_scale;
	map->reset_scale = reset_scale;
	return (1);
}
