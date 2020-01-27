/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 15:49:18 by ohakola          ###   ########.fr       */
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
	while (++i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
			connect_map_pts_with_gradient(line_connect,
				scene->map->vertices[i],
					scene->map->vertices[i + 1]);
		if (i < scene->map->vertex_count - scene->map->x - 1)
			connect_map_pts_with_gradient(line_connect,
				scene->map->vertices[i],
					scene->map->vertices[i + 1 + scene->map->x]);
	}
	free(line_connect);
}
