/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:36:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 12:37:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_vertex_limits(t_map *map, t_vector *vertex)
{
	map->x_max = map->x_max >= vertex->v[0] ? map->x_max : vertex->v[0];
	map->x_min = map->x_min <= vertex->v[0] ? map->x_min : vertex->v[0];
	map->y_max = map->y_max >= vertex->v[1] ? map->y_max : vertex->v[1];
	map->y_min = map->y_min <= vertex->v[1] ? map->y_min : vertex->v[1];
	map->z_max = map->z_max >= vertex->v[2] ? map->z_max : vertex->v[2];
	map->z_min = map->z_min <= vertex->v[2] ? map->z_min : vertex->v[2];
}

static void		reset_xyz_minmaxes(t_map *map)
{
	map->x_max = 0;
	map->x_min = 0;
	map->y_max = 0;
	map->y_min = 0;
	map->z_max = 0;
	map->z_min = 0;
}

int				center_and_set_map_vertices(t_list *vtx_lst, t_map *map)
{
	t_vector	**vs;
	t_vector	*shift;
	size_t		i;

	if ((vs = (t_vector**)malloc(sizeof(*vs) * map->vertex_count)) == NULL ||
		(shift = ft_vector4_new(
			-map->x_max / 2, -map->y_max / 2,
			0)) == NULL)
		return (0);
	reset_xyz_minmaxes(map);
	i = 0;
	while (vtx_lst)
	{
		vs[i] = (t_vector*)(vtx_lst->content);
		if (ft_vector_add(vs[i], shift, vs[i]) == FALSE)
			return (0);
		set_vertex_limits(map, vs[i]);
		vs[i++]->v[3] = 1;
		vtx_lst = vtx_lst->next;
	}
	map->vertices = vs;
	ft_vector_free(shift);
	free(vtx_lst);
	return (1);
}

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

int				scale_map_z(t_map *map, double amount)
{
	t_vector	*scale;
	t_matrix	*scale_m;

	if ((scale = ft_vector4_new(1, 1, amount)) == NULL ||
		(scale_m = ft_scale_matrix(4, 4, scale)) == NULL ||
		ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) == FALSE ||
		ft_matrix_mul_vector_lst(scale_m, map->vertices,
			map->vertex_count) == FALSE ||
		ft_matrix_mul_vector_lst(map->rotation, map->vertices,
			map->vertex_count) == FALSE)
		return (0);
	ft_vector_free(scale);
	ft_matrix_free(scale_m);
	return (1);
}
