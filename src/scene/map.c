/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/29 17:17:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Map vertex drawing algorithm to connect each vertex correctly
** to screen. Each position is connected to their right and bottom
** vertices:
** *--->*
** |
** v
** *
*/

void			draw_map_on_frame(t_scene *scene)
{
	t_edge			edge;
	size_t			i;

	i = -1;
	while (++i < scene->maps[scene->map_index]->vertex_count - 1)
	{
		if ((i + 1) % (scene->maps[scene->map_index]->x + 1) != 0)
		{
			edge = (t_edge){.scene = scene,
			.point1 = scene->maps[scene->map_index]->vertices[i],
			.point2 = scene->maps[scene->map_index]->vertices[i + 1],
			.color_start = 0, .color_end = 0};
			connect_map_pts_with_gradient(&edge);
		}
		if (i < scene->maps[scene->map_index]->vertex_count -
			scene->maps[scene->map_index]->x - 1)
		{
			edge = (t_edge){.scene = scene,
			.point1 = scene->maps[scene->map_index]->vertices[i],
			.point2 = scene->maps[scene->map_index]->vertices[
						i + 1 + scene->maps[scene->map_index]->x],
			.color_start = 0, .color_end = 0};
			connect_map_pts_with_gradient(&edge);
		}
	}
}
