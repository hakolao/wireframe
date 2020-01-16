/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:18:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/16 11:22:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void			plot_pixel(int x, int y, int color, t_scene *scene)
{
	mlx_pixel_put(
		scene->mlx,
		scene->mlx_wdw,
		x + WINDOW_WIDTH / 2,
		y + WINDOW_HEIGHT / 2,
	color);
}

static void			plot_line_low(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
	t_line	line;

	line.yi = 1;
	line.dx = point2->v[0] - point1->v[0];
	line.dy = point2->v[1] - point1->v[1];
	if (line.dy < 0)
	{
		line.yi = -1;
		line.dy = -line.dy;
	}
	line.p = 2 * line.dy - line.dx;
	line.y = point1->v[1];
	line.x = point1->v[0];
	while (line.x < point2->v[0])
	{
		plot_pixel(line.x, line.y, color, scene);
		if (line.p > 0)
		{
			line.y += line.yi;
			line.p += -2 * line.dx;
		}
		line.p += 2 * line.dy;
		line.x += 1;
	}
}

static void			plot_line_high(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
	t_line	line;

	line.xi = 1;
	line.dx = point2->v[0] - point1->v[0];
	line.dy = point2->v[1] - point1->v[1];
	if (line.dx < 0)
	{
		line.xi = -1;
		line.dx = -line.dx;
	}
	line.p = 2 * line.dx - line.dy;
	line.y = point1->v[1];
	line.x = point1->v[0];
	while (line.y < point2->v[1])
	{
		plot_pixel(line.x, line.y, color, scene);
		if (line.p > 0)
		{
			line.x += line.xi;
			line.p += -2 * line.dy;
		}
		line.p += 2 * line.dx;
		line.y += 1;
	}
}

/*
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization
*/

void			draw_line(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
	int	x2;
	int	x1;
	int y2;
	int	y1;
	
	x2 = point2->v[0];
	x1 = point1->v[0];
	y2 = point2->v[1];
	y1 = point1->v[1];
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			plot_line_low(point2, point1, color, scene);
		else
			plot_line_low(point1, point2, color, scene);
	}
	else
	{
		if (y1 > y2)
			plot_line_high(point2, point1, color, scene);
		else
			plot_line_high(point1, point2, color, scene);
	}
	ft_vector_free(point1);
	ft_vector_free(point2);
}