/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:18:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 12:16:21 by ohakola          ###   ########.fr       */
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

static double			calculate_steps(int	x_or_y, int end)
{
	double	steps;
	
	steps = 0;
	while (x_or_y < end)
	{
		x_or_y++;
		steps++;
	}
	return (steps);
}

static void			plot_line_low(t_line_connect *line_connect)
{
	t_line		line;
	double		steps;
	double		step;

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
	steps = calculate_steps(line.x, line_connect->point2->v[0]);
	step = 0;
	while (line.x < line_connect->point2->v[0])
	{
		plot_pixel(line.x, line.y,
			COLOR(
				RED(line_connect->color_start) + (int)((1 - step / steps) * (RED(line_connect->color_start) - RED(line_connect->color_end))),
				GREEN(line_connect->color_start) + (int)((1 - step / steps) * (GREEN(line_connect->color_start) - GREEN(line_connect->color_end))),
				BLUE(line_connect->color_start) + (int)((1 - step / steps) * (BLUE(line_connect->color_start) - BLUE(line_connect->color_end)))
			),
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
	steps = calculate_steps(line.y, line_connect->point2->v[1]);
	step = 0;
	while (line.y < line_connect->point2->v[1])
	{
		plot_pixel(line.x, line.y,
			COLOR(
				RED(line_connect->color_start) + (int)((1 - step / steps) * (RED(line_connect->color_start) - RED(line_connect->color_end))),
				GREEN(line_connect->color_start) + (int)((1 - step / steps) * (GREEN(line_connect->color_start) - GREEN(line_connect->color_end))),
				BLUE(line_connect->color_start) + (int)((1 - step / steps) * (BLUE(line_connect->color_start) - BLUE(line_connect->color_end)))
			),
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

static void			good_old_swap(t_line_connect *line_connect)
{
	t_vector	*tmp;

	tmp = line_connect->point2;
	line_connect->point2 = line_connect->point1;
	line_connect->point1 = tmp;
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
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			good_old_swap(line_connect);
		plot_line_low(line_connect);
	}
	else
	{
		if (y1 > y2)
			good_old_swap(line_connect);
		plot_line_high(line_connect);
	}
}
