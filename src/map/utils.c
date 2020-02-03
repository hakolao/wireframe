/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:36:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 15:31:53 by ohakola          ###   ########.fr       */
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

/*
** Rotates map by given x, y, z angles
*/

int				rotate_map(t_map *map, int amount_x, int amount_y, int amount_z)
{
	t_matrix	rotation;
	t_matrix	map_rotation;
	t_matrix	reset_rotation;

	map_rotation = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	rotation = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	reset_rotation = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	if (!ft_rotation_matrix(amount_x, amount_y, amount_z, &rotation) ||
		!ft_matrix_mul(&rotation, map->rotation, &map_rotation) ||
		!ft_matrix_mul_vector_lst(&rotation, map->vertices,
			map->vertex_count) ||
		!ft_matrix_inverse_4x4(&map_rotation, &reset_rotation))
		return (0);
	ft_matrix_set_vals(map->rotation, map_rotation.m, 16);
	ft_matrix_set_vals(map->reset_rotation, reset_rotation.m, 16);
	return (1);
}

/*
** Scales map by given x y z scale amounts
*/

int				scale_map(t_map *map, double x, double y, double z)
{
	t_vector	scale;
	t_matrix	scale_m;
	t_matrix	map_scale;
	t_matrix	reset_scale;

	scale = (t_vector){.v = (double[]){x, y, z, 1}, .size = 4};
	scale_m = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	map_scale = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	reset_scale = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	if (!ft_scale_matrix(4, 4, &scale, &scale_m) ||
		!ft_matrix_mul(map->scale, &scale_m, &map_scale) ||
		!ft_matrix_inverse_4x4(&map_scale, &reset_scale) ||
		!ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) ||
		!ft_matrix_mul_vector_lst(&scale_m, map->vertices,
			map->vertex_count) ||
		set_map_info(map) ||
		!ft_matrix_mul_vector_lst(map->rotation, map->vertices,
			map->vertex_count))
		return (0);
	ft_matrix_set_vals(map->scale, map_scale.m, 16);
	ft_matrix_set_vals(map->reset_scale, reset_scale.m, 16);
	return (1);
}
