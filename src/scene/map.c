/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 19:37:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Connect map edge
*/

static void		connect_edge(t_scene *scene, t_vector *point1,
				t_vector *point2)
{
	t_edge			edge;

	edge = (t_edge){.scene = scene,
					.point1 = point1,
					.point2 = point2,
					.color_start = 0,
					.color_end = 0};
	connect_map_edge_gradient(&edge);
}

/*
** Map vertex drawing algorithm to connect each vertex correctly
** to screen. Each position is connected as triangles
** A->B, B->C, C->A, A->C, C->D, D->A
** vertices:
** A----B
** |    |
** D----C
** C->A amd A->C are the same, so one can be left out
*/

void			draw_map_on_frame(t_scene *scene)
{
	size_t			i;

	i = -1;
	while (++i < scene->maps[scene->map_index]->vertex_count -
			scene->maps[scene->map_index]->x - 2)
	{
		if ((i + 1) % (scene->maps[scene->map_index]->x + 1) != 0)
		{
			connect_edge(scene, scene->maps[scene->map_index]->vertices[i],
						scene->maps[scene->map_index]->vertices[i + 1]);
			connect_edge(scene, scene->maps[scene->map_index]->vertices[i + 1],
								scene->maps[scene->map_index]->vertices[
								i + 2 + scene->maps[scene->map_index]->x]);
			connect_edge(scene, scene->maps[scene->map_index]->vertices[
								i + 2 + scene->maps[scene->map_index]->x],
						scene->maps[scene->map_index]->vertices[i]);
			connect_edge(scene, scene->maps[scene->map_index]->vertices[
								i + 2 + scene->maps[scene->map_index]->x],
								scene->maps[scene->map_index]->vertices[
								i + 1 + scene->maps[scene->map_index]->x]);
			connect_edge(scene, scene->maps[scene->map_index]->vertices[
								i + 1 + scene->maps[scene->map_index]->x],
								scene->maps[scene->map_index]->vertices[i]);
		}
	}
}

/*
** Get initial z scale (most maps have z too large relative to x, y)
*/

double			init_zscale(t_map *map)
{
	return ((map->y_max - map->y_min) /
			(8 * (map->z_max - map->z_min + 0.1)));
}
