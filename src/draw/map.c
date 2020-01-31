/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/31 21:14:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Connects triangle edges
*/

static void		connect_triangle(t_scene *scene, t_vector *a,
				t_vector *b, t_vector *c)
{
	t_edge ab;
	t_edge bc;
	t_edge ca;

	ab = (t_edge){.scene = scene, .point1 = a, .point2 = b,
		.color_start = 0, .color_end = 0};
	bc = (t_edge){.scene = scene, .point1 = b, .point2 = c,
		.color_start = 0, .color_end = 0};
	ca = (t_edge){.scene = scene, .point1 = c, .point2 = a,
		.color_start = 0, .color_end = 0};
	connect_edge_with_gradient(&ab);
	connect_edge_with_gradient(&bc);
	connect_edge_with_gradient(&ca);
}

/*
** Map vertex drawing algorithm to connect each vertex correctly
** to screen. Each position is connected as triangles
** A->C, C->B, B->A, A->D, D->C, C->A
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
			connect_triangle(scene,
				scene->maps[scene->map_index]->vertices[
					i + 2 + scene->maps[scene->map_index]->x],
				scene->maps[scene->map_index]->vertices[i + 1],
				scene->maps[scene->map_index]->vertices[i]);
			connect_triangle(scene,
				scene->maps[scene->map_index]->vertices[i],
				scene->maps[scene->map_index]->vertices[
					i + 1 + scene->maps[scene->map_index]->x],
				scene->maps[scene->map_index]->vertices[
					i + 2 + scene->maps[scene->map_index]->x]);
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
