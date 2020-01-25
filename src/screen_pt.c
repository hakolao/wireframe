/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_pt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:26:52 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 19:05:09 by ohakola          ###   ########.fr       */
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
	draw_line(line_connect);
	ft_vector_free(s1);
	ft_vector_free(s2);
}

/*
** Helper function which exposes line connecting for map including color for
** map's gradient.
*/

void				connect_map_pts_with_gradient(t_line_connect *line_connect,
					t_vector *point1, t_vector *point2)
{
	t_vector	*reset_p1;
	t_vector	*reset_p2;
	double		in[2];
	double		out[2];

	line_connect->point1 = point1;
	line_connect->point2 = point2;
	if ((reset_p1 = ft_vector_new(4)) == NULL || ft_matrix_mul_vector(
		line_connect->scene->map->reset_rotation, point1, reset_p1) == FALSE)
		return ;
	line_connect->color_start = map_color(gradient_multiplier(in, out, reset_p1,
		line_connect->scene->map));
	if ((reset_p2 = ft_vector_new(4)) == NULL || ft_matrix_mul_vector(
		line_connect->scene->map->reset_rotation, point2, reset_p2) == FALSE)
		return ;
	line_connect->color_end = map_color(gradient_multiplier(in, out, reset_p2,
		line_connect->scene->map));
	if (reset_p1->v[2] < reset_p2->v[2])
		swap_points_in_line_connect(line_connect);
	ft_vector_free(reset_p1);
	ft_vector_free(reset_p2);
	connect_points(line_connect);
}
