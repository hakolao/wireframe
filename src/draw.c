/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 21:17:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Transforms vertex into screen space
*/

int					screen_pt(t_vector *point, t_scene *scene,
					t_vector *res)
{
	if (!ft_matrix_mul_vector(scene->camera->transform, point, res))
		return (0);
	res->v[0] /= res->v[3];
	res->v[1] /= res->v[3];
	res->v[2] /= res->v[3];
	res->v[3] /= res->v[3];
	return (1);
}

/*
** Checks if given point is in front of camera, if not, it should
** not be drawn.
*/

int					in_front_of_camera(t_vector *p, t_camera *camera)
{
	t_vector	c;
	
	c = (t_vector){.v = (double[4]){0}, .size = 4};
	return (ft_matrix_mul_vector(camera->view, p, &c)
			&& c.v[2] > 0 && c.v[2] > 0);
}

/*
** Connects given points in edge only if they are within screen
** coordinates
*/

void				connect_edge(t_edge *edge)
{
	if (edge->screen1->v[0] >= 0 && edge->screen1->v[0] <= WIDTH &&
		edge->screen1->v[1] >= 0 && edge->screen1->v[1] <= HEIGHT &&
		edge->screen2->v[0] >= 0 && edge->screen2->v[0] <= WIDTH &&
		edge->screen2->v[1] >= 0 && edge->screen2->v[1] <= HEIGHT)
		draw_line(edge);
}

/*
** Reset frame color to original values
*/

static void			clear_frame(t_scene *scene)
{
	int		x;
	int		y;
	int		pixel;
	int		color;

	color = COLOR(scene->col_r, scene->col_g, scene->col_b, scene->col_a);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = y * scene->line_bytes + x * 4;
			scene->frame_buf[pixel] = BLUE(color);
			scene->frame_buf[pixel + 1] = GREEN(color);
			scene->frame_buf[pixel + 2] = RED(color);
			scene->frame_buf[pixel + 3] = ALPHA(color);
			x++;
		}
		y++;
	}
}

/*
** Draw loop to draw fdf content
*/

int					draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	clear_frame(scene);
	draw_map_on_frame(scene);
	mlx_put_image_to_window(scene->mlx, scene->mlx_wdw, scene->frame, 0, 0);
	draw_ui(scene);
	scene->redraw = FALSE;
	return (1);
}
