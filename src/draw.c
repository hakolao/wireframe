/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 15:45:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int		*point_to_screen(t_point *point, t_scene *scene)
{
	int		*xy;
	int		x_in_minmax[2];
	int		x_out_minmax[2];
	int		y_in_minmax[2];
	int		y_out_minmax[2];

	x_in_minmax[0] = 0;
	x_in_minmax[1] = (int)(scene->map->x_max);
	x_out_minmax[0] = 0;
	x_out_minmax[1] = WINDOW_WIDTH;
	y_in_minmax[0] = 0;
	y_in_minmax[1] = (int)(scene->map->y_max);
	y_out_minmax[0] = 0;
	y_out_minmax[1] = WINDOW_HEIGHT;
	if ((xy = (int*)malloc(sizeof(*xy) * 2)) == NULL)
		return (NULL);
	xy[0] = ft_lmap_int(point->x, x_in_minmax,  x_out_minmax);
	xy[1] = ft_lmap_int(point->y, y_in_minmax,  y_out_minmax);
	return (xy);
}

static void		draw_pixel(void *mlx, void *mlx_wdw, t_point *point, t_scene *scene)
{
	int		*xy;
	int		color;

	if ((xy = point_to_screen(point, scene)) == NULL)
	{
		log_error("Unknown", "Error:");
		return ;
	};
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