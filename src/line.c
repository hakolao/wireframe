/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:18:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:01:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Renders pixel to screen to x y position including a dynamically
** calculated gradient color
*/

static void			plot_pixel(int x, int y, t_edge *edge,
					double grad_mul)
{
	int	color;
	int	pixel;

	color = grad_color(edge->color_start,
			edge->color_end, grad_mul);
	pixel = (y * edge->scene->line_bytes) + (x * 4);
	if (pixel > 0 && pixel < HEIGHT * WIDTH * 4)
	{
		edge->scene->frame_buf[pixel + 0] = BLUE(color);
		edge->scene->frame_buf[pixel + 1] = GREEN(color);
		edge->scene->frame_buf[pixel + 2] = RED(color);
		edge->scene->frame_buf[pixel + 3] = ALPHA(color);
	}
}

static void			plot_line_low(t_edge *edge)
{
	t_line		line;
	double		steps;
	double		step;

	line.dx = edge->screen2->v[0] - edge->screen1->v[0];
	line.dy = edge->screen2->v[1] - edge->screen1->v[1];
	line.yi = line.dy < 0 ? -1 : 1;
	line.dy = line.dy < 0 ? -line.dy : line.dy;
	line.p = 2 * line.dy - line.dx;
	line.y = edge->screen1->v[1];
	line.x = edge->screen1->v[0];
	steps = edge->screen2->v[0] - line.x;
	step = 0;
	while (line.x < edge->screen2->v[0])
	{
		plot_pixel(line.x, line.y, edge, step / steps);
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

static void			plot_line_high(t_edge *edge)
{
	t_line		line;
	double		steps;
	double		step;

	line.dx = edge->screen2->v[0] - edge->screen1->v[0];
	line.dy = edge->screen2->v[1] - edge->screen1->v[1];
	line.xi = line.dx < 0 ? -1 : 1;
	line.dx = line.dx < 0 ? -line.dx : line.dx;
	line.p = 2 * line.dx - line.dy;
	line.y = edge->screen1->v[1];
	line.x = edge->screen1->v[0];
	steps = edge->screen2->v[1] - line.y;
	step = 0;
	while (line.y < edge->screen2->v[1])
	{
		plot_pixel(line.x, line.y, edge, step / steps);
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

/*
** Swaps points, start & end color in line drawing special case
*/

void				swap_points_in_edge(t_edge *edge)
{
	t_vector	*tmp;
	int			tmp_color;

	tmp = edge->point2;
	edge->point2 = edge->point1;
	edge->point1 = tmp;
	tmp = edge->screen2;
	edge->screen2 = edge->screen1;
	edge->screen1 = tmp;
	tmp = edge->original2;
	edge->original2 = edge->original1;
	edge->original1 = tmp;
	tmp_color = edge->color_start;
	edge->color_start = edge->color_end;
	edge->color_end = tmp_color;
}

/*
** Bresenham's line drawing algorithm including gradient calculations
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization
*/

void				draw_line(t_edge *edge)
{
	int			x2;
	int			x1;
	int			y2;
	int			y1;

	x2 = edge->screen2->v[0];
	x1 = edge->screen1->v[0];
	y2 = edge->screen2->v[1];
	y1 = edge->screen1->v[1];
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			swap_points_in_edge(edge);
		plot_line_low(edge);
	}
	else
	{
		if (y1 > y2)
			swap_points_in_edge(edge);
		plot_line_high(edge);
	}
}
