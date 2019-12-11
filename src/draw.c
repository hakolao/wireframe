/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 14:43:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int		*point_to_screen(t_point *point, t_scene *scene)
{
	
}

static void		draw_pixel(void *mlx, void *mlx_wdw, t_point *point, t_scene *scene)
{
	int		*xy;
	int		color;

	xy = point_to_screen(point, scene);
	color = ft_rgbtoi(scene->camera->color->r,
						scene->camera->color->g,
						scene->camera->color->b);
	mlx_pixel_put(mlx, mlx_wdw, xy[0], xy[1], color);
}

void	draw(void *mlx, void *mlx_wdw, t_scene *scene)
{
	t_list	*vertex;

	vertex = scene->map->vertices;
	while (vertex)
	{
		draw_pixel(mlx, mlx_wdw, (t_point*)vertex->content, scene);
		vertex = vertex->next;
	}
}