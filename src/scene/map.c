/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 14:20:20 by ohakola          ###   ########.fr       */
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
	t_line_connect	*line_connect;
	size_t			i;

	if ((line_connect = malloc(sizeof(t_line_connect))) == NULL)
		return ;
	line_connect->scene = scene;
	i = -1;
	while (++i < scene->maps[scene->map_index]->vertex_count - 1)
	{
		if ((i + 1) % (scene->maps[scene->map_index]->x + 1) != 0)
			connect_map_pts_with_gradient(line_connect,
				scene->maps[scene->map_index]->vertices[i],
					scene->maps[scene->map_index]->vertices[i + 1]);
		if (i < scene->maps[scene->map_index]->vertex_count -
			scene->maps[scene->map_index]->x - 1)
			connect_map_pts_with_gradient(line_connect,
				scene->maps[scene->map_index]->vertices[i],
					scene->maps[scene->map_index]->vertices[
						i + 1 + scene->maps[scene->map_index]->x]);
	}
	free(line_connect);
}
