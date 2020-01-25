/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 19:05:50 by ohakola          ###   ########.fr       */
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
				BLUE(start) + (int)(gradient_mul * ft_abs(b_diff))));
}

/*
** Swaps points, start & end color in line drawing special case
*/

void			swap_points_in_line_connect(t_line_connect *line_connect)
{
	t_vector	*tmp;
	int			tmp_color;

	tmp = line_connect->point2;
	line_connect->point2 = line_connect->point1;
	line_connect->point1 = tmp;
	tmp_color = line_connect->color_start;
	line_connect->color_start = line_connect->color_end;
	line_connect->color_end = tmp_color;
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

int				map_color(double mul)
{
	return (COLOR((int)(0.5 * (1 + sin(mul)) * 255 + (mul > 1 ? 255 : 0)),
			(int)(cos(mul) * 255 + (mul > 1 ? 255 : 0)),
			(int)(sin(mul) * sin(mul) * 255 + (mul > 1 ? 255 : 0))));
}
