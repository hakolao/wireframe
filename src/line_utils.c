/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 17:05:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

double			set_gradient_multiplier(double *in_minmax, double *out_minmax,
				t_vector *point, t_map *map)
{
	in_minmax[0] = map->z_min;
	in_minmax[1] = map->z_max;
	out_minmax[0] = 0.3;
	out_minmax[1] = 1.3;
	return (ft_lmap_double(point->v[2], in_minmax, out_minmax));
}
