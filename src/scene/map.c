/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 18:33:33 by ohakola          ###   ########.fr       */
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
	t_edge			*edge;
	size_t			i;

	if ((edge = malloc(sizeof(t_edge))) == NULL)
		return ;
	edge->scene = scene;
	i = -1;
	while (++i < scene->maps[scene->map_index]->vertex_count - 1)
	{
		if ((i + 1) % (scene->maps[scene->map_index]->x + 1) != 0)
			connect_map_pts_with_gradient(edge,
				scene->maps[scene->map_index]->vertices[i],
					scene->maps[scene->map_index]->vertices[i + 1]);
		if (i < scene->maps[scene->map_index]->vertex_count -
			scene->maps[scene->map_index]->x - 1)
			connect_map_pts_with_gradient(edge,
				scene->maps[scene->map_index]->vertices[i],
					scene->maps[scene->map_index]->vertices[
						i + 1 + scene->maps[scene->map_index]->x]);
	}
	free(edge);
}
