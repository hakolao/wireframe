/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 18:01:24 by ohakola          ###   ########.fr       */
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

double			height_multiplier(t_vector *point, t_map *map)
{
	double in_minmax[2];
	double out_minmax[2];
	
	in_minmax[0] = map->z_min - 0.1;
	in_minmax[1] = map->z_max + 0.1;
	out_minmax[0] = -M_PI / 2;
	out_minmax[1] = M_PI / 2;
	return (ft_lmap_double(point->v[2], in_minmax, out_minmax));
}

/*
** Calculates map's gradient color based on multiplier.
** Multiplier is a clamped value (a result from gradient_multiplier
** function)
*/

int				map_color(t_vector *point, t_scene *scene)
{
	t_map	*map;
	double	mul;

	map = scene->maps[scene->map_index];
	mul = height_multiplier(point, map);
	return (COLOR(
		(int)(0.5 * (1 + sin((2 * mul - M_PI / 4) / 2)) * map->col_r),
		(int)(cos(mul) * cos(mul) * map->col_g),
		(int)(0.5 * (1 + cos((mul + M_PI / 2) * 1.2)) * map->col_b),
		map->col_a));
}
