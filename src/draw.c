/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 12:02:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Transforms vertex into screen space
*/

t_vector			*screen_pt(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(
			scene->camera->transform, point, on_screen) == FALSE)
		return (NULL);
	on_screen->v[0] /= on_screen->v[3];
	on_screen->v[1] /= on_screen->v[3];
	on_screen->v[2] /= on_screen->v[3];
	on_screen->v[3] /= on_screen->v[3];
	return (on_screen);
}

/*
** Checks if given point is in front of camera, if not, it should
** not be drawn.
*/

static int			in_front_of_camera(t_vector *p1, t_vector *p2,
					t_camera *camera)
{
	t_vector	*c1;
	t_vector	*c2;
	int			ret;

	if ((c1 = ft_vector_new(4)) == NULL ||
		(c2 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(camera->view, p1, c1) == FALSE ||
		ft_matrix_mul_vector(camera->view, p2, c2) == FALSE)
		return (0);
	ret = c1->v[2] > 0.5 && c2->v[2] > 0.5;
	ft_vector_free(c1);
	ft_vector_free(c2);
	return (ret);
}

/*
** Connects given points from line_connect struct by drawing a line
** between those points in screen space.
** Points are first validated by in_front_of_camera and then brought
** to screen space before passing to draw_line.
** Half screen width and height are added to screen x & screen y.
** Line is drawn only if point lies within window.
*/

void				connect_points(t_line_connect *line_connect)
{
	t_vector	*s1;
	t_vector	*s2;

	if (!in_front_of_camera(line_connect->point1,
		line_connect->point2,
		line_connect->scene->camera))
		return ;
	if (((s1 = screen_pt(line_connect->point1, line_connect->scene)) == NULL ||
		(s2 = screen_pt(line_connect->point2, line_connect->scene)) == NULL) &&
		log_error("Something failed in point_to_screen.", ""))
		exit(1);
	line_connect->point1 = s1;
	line_connect->point2 = s2;
	s1->v[0] += WINDOW_WIDTH / 2;
	s1->v[1] += WINDOW_HEIGHT / 2;
	s2->v[0] += WINDOW_WIDTH / 2;
	s2->v[1] += WINDOW_HEIGHT / 2;
	if (s1->v[0] >= 0 && s1->v[0] <= WINDOW_WIDTH &&
		s1->v[1] >= 0 && s1->v[1] <= WINDOW_HEIGHT &&
		s2->v[0] >= 0 && s2->v[0] <= WINDOW_WIDTH &&
		s2->v[1] >= 0 && s2->v[1] <= WINDOW_HEIGHT)
		draw_line(line_connect);
	ft_vector_free(s1);
	ft_vector_free(s2);
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
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
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
