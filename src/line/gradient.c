/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 14:11:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Returns a gradient color based on linear step between screen point1
** and screen point 2 (used in line drawing)
*/

int				grad_color(int start, int end, double gradient_mul)
{
	int r_diff;
	int	g_diff;
	int	b_diff;

	r_diff = RED(start) - RED(end);
	g_diff = GREEN(start) - GREEN(end);
	b_diff = BLUE(start) - BLUE(end);
	return (COLOR(
			r_diff > 0 ? RED(start) - (int)(gradient_mul * ft_abs(r_diff)) :
				RED(start) + (int)(gradient_mul * ft_abs(r_diff)),
			g_diff > 0 ? GREEN(start) - (int)(gradient_mul * ft_abs(g_diff)) :
				GREEN(start) + (int)(gradient_mul * ft_abs(g_diff)),
			b_diff > 0 ? BLUE(start) - (int)(gradient_mul * ft_abs(b_diff)) :
				BLUE(start) + (int)(gradient_mul * ft_abs(b_diff)), 0));
}

/*
** Maps height value between out_minmax values linearly.
*/

double			gradient_multiplier(double *in_minmax, double *out_minmax,
				t_vector *point, t_map *map)
{
	in_minmax[0] = map->z_min;
	in_minmax[1] = map->z_max;
	out_minmax[0] = -M_PI / 2;
	out_minmax[1] = M_PI / 2;
	return (ft_lmap_double(point->v[2], in_minmax, out_minmax));
}

/*
** Calculates map's gradient color based on multiplier.
** Multiplier is a clamped value (a result from gradient_multiplier
** function)
*/

static int		map_color(double mul, t_scene *scene)
{
	return (COLOR(
		(int)(0.5 * (1 + sin(mul)) *
			scene->col_r + (mul > 1 ? scene->col_r : 0)),
		(int)(cos(mul) *
			scene->col_g + (mul > 1 ? scene->col_g : 0)),
		(int)(sin(mul) *
			sin(mul) * scene->col_b + (mul > 1 ? scene->col_b : 0)), 0));
}

/*
** Helper function which exposes line connecting for map including color for
** map's gradient.
*/

void			connect_map_pts_with_gradient(t_line_connect *line_connect,
				t_vector *point1, t_vector *point2)
{
	t_vector	*reset_p1;
	t_vector	*reset_p2;
	double		in[2];
	double		out[2];
	int			map_i;

	line_connect->point1 = point1;
	line_connect->point2 = point2;
	map_i = line_connect->scene->map_index;
	if ((reset_p1 = ft_vector_new(4)) == NULL || !ft_matrix_mul_vector(
		line_connect->scene->maps[map_i]->reset_rotation, point1, reset_p1))
		return ;
	line_connect->color_start = map_color(gradient_multiplier(in, out, reset_p1,
		line_connect->scene->maps[map_i]), line_connect->scene);
	if ((reset_p2 = ft_vector_new(4)) == NULL || !ft_matrix_mul_vector(
		line_connect->scene->maps[map_i]->reset_rotation, point2, reset_p2))
		return ;
	line_connect->color_end = map_color(gradient_multiplier(in, out, reset_p2,
		line_connect->scene->maps[map_i]), line_connect->scene);
	if (reset_p1->v[2] < reset_p2->v[2])
		swap_points_in_line_connect(line_connect);
	ft_vector_free(reset_p1);
	ft_vector_free(reset_p2);
	connect_points(line_connect);
}
