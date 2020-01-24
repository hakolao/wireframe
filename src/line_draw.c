/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:18:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 16:27:12 by ohakola          ###   ########.fr       */
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

static int			grad_color(int start, int end, double gradient_mul)
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
				BLUE(start) + (int)(gradient_mul * ft_abs(b_diff))
		));
}

static void			plot_line_low(t_line_connect *line_connect)
{
	t_line		line;
	double		steps;
	double		step;
	double		gradient_mul;

	line.yi = 1;
	line.dx = line_connect->point2->v[0] - line_connect->point1->v[0];
	line.dy = line_connect->point2->v[1] - line_connect->point1->v[1];
	if (line.dy < 0)
	{
		line.yi = -1;
		line.dy = -line.dy;
	}
	line.p = 2 * line.dy - line.dx;
	line.y = line_connect->point1->v[1];
	line.x = line_connect->point1->v[0];
	steps = line_connect->point2->v[0] - line.x;
	step = 0;
	while (line.x < line_connect->point2->v[0])
	{
		gradient_mul = line_connect->direction > 0 ? step / step : 1 - step / step;
		plot_pixel(line.x, line.y,
			grad_color(line_connect->color_start,
				line_connect->color_end, gradient_mul),
			line_connect->scene);
		if (line.p > 0)
		{
			line.y += line.yi;
			line.p += -2 * line.dx;
		}
		line.p += 2 * line.dy;
		line.x += 1;
		step++;
	}
}

static void			plot_line_high(t_line_connect *line_connect)
{
	t_line		line;
	double		steps;
	double		step;
	double		gradient_mul;

	line.xi = 1;
	line.dx = line_connect->point2->v[0] - line_connect->point1->v[0];
	line.dy = line_connect->point2->v[1] - line_connect->point1->v[1];
	if (line.dx < 0)
	{
		line.xi = -1;
		line.dx = -line.dx;
	}
	line.p = 2 * line.dx - line.dy;
	line.y = line_connect->point1->v[1];
	line.x = line_connect->point1->v[0];
	steps = line_connect->point2->v[1] - line.y;
	step = 0;
	while (line.y < line_connect->point2->v[1])
	{
		gradient_mul = line_connect->direction > 0 ? step / step : 1 - step / step;
		plot_pixel(line.x, line.y,
			grad_color(line_connect->color_start,
				line_connect->color_end, gradient_mul),
			line_connect->scene);
		if (line.p > 0)
		{
			line.x += line.xi;
			line.p += -2 * line.dy;
		}
		line.p += 2 * line.dx;
		line.y += 1;
		step++;
	}
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
	line_connect->direction = -1;
}

/*
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization
*/

void				draw_line(t_line_connect *line_connect)
{
	int			x2;
	int			x1;
	int			y2;
	int			y1;

	x2 = line_connect->point2->v[0];
	x1 = line_connect->point1->v[0];
	y2 = line_connect->point2->v[1];
	y1 = line_connect->point1->v[1];
	line_connect->direction = 1;
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			swap_points_in_line_connect(line_connect);
		plot_line_low(line_connect);
	}
	else
	{
		if (y1 > y2)
			swap_points_in_line_connect(line_connect);
		plot_line_high(line_connect);
	}
}
