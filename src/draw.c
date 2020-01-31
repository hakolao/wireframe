/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/31 16:50:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Transforms vertex into screen space
*/

static int			screen_pt(t_vector *point, t_scene *scene,
					t_vector *on_screen)
{
	if (!ft_matrix_mul_vector(scene->camera->transform, point, on_screen))
		return (0);
	on_screen->v[0] /= on_screen->v[3];
	on_screen->v[1] /= on_screen->v[3];
	on_screen->v[2] /= on_screen->v[3];
	on_screen->v[3] /= on_screen->v[3];
	return (1);
}

/*
** Checks if given point is in front of camera, if not, it should
** not be drawn.
*/

int					in_front_of_camera(t_vector *p1, t_vector *p2,
					t_camera *camera)
{
	t_vector	c1;
	t_vector	c2;
	int			ret;

	c1 = (t_vector){.v = (double[]){0, 0, 0, 0}, .size = 4};
	c2 = (t_vector){.v = (double[]){0, 0, 0, 0}, .size = 4};
	if (ft_matrix_mul_vector(camera->view, p1, &c1) == FALSE ||
		ft_matrix_mul_vector(camera->view, p2, &c2) == FALSE)
		return (0);
	ret = c1.v[2] > 0 && c2.v[2] > 0;
	return (ret);
}

/*
** Connects given points from edge struct by drawing a line
** between those points in screen space.
** Points are first validated by in_front_of_camera and then brought
** to screen space before passing to draw_line.
** Half screen width and height are added to screen x & screen y.
** Line is drawn only if point lies within window.
*/

void				connect_points(t_edge *edge)
{
	t_vector	s1;
	t_vector	s2;

	if (!in_front_of_camera(edge->point1, edge->point2,
			edge->scene->camera))
		return ;
	s1 = (t_vector){.v = (double[]){0, 0, 0, 0}, .size = 4};
	s2 = (t_vector){.v = (double[]){0, 0, 0, 0}, .size = 4};
	if ((!screen_pt(edge->point1, edge->scene, &s1) ||
		!screen_pt(edge->point2, edge->scene, &s2)) &&
		log_err("Something failed in point_to_screen.", ""))
		exit(1);
	edge->point1 = &s1;
	edge->point2 = &s2;
	s1.v[0] += WIDTH / 2;
	s1.v[1] += HEIGHT / 2;
	s2.v[0] += WIDTH / 2;
	s2.v[1] += HEIGHT / 2;
	if (s1.v[0] >= 0 && s1.v[0] <= WIDTH &&
		s1.v[1] >= 0 && s1.v[1] <= HEIGHT &&
		s2.v[0] >= 0 && s2.v[0] <= WIDTH &&
		s2.v[1] >= 0 && s2.v[1] <= HEIGHT)
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
	draw_axes_on_frame(scene);
	mlx_put_image_to_window(scene->mlx, scene->mlx_wdw, scene->frame, 0, 0);
	draw_ui(scene);
	scene->redraw = FALSE;
	return (1);
}
