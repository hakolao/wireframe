/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 20:04:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector			*point_to_screen(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(scene->camera->transform, point, on_screen) == 0)
		return (NULL);
	return (on_screen);
}

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
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	yi;
	int	p;

	yi = 1;
	dx = point2->v[0] - point1->v[0];
	dy = point2->v[1] - point1->v[1];
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	p = 2 * dy - dx;
	y = point1->v[1];
	x = point1->v[0];
	while (x < point2->v[0])
	{
		plot_pixel(x, y, color, scene);
		if (p > 0)
		{
			y = y + yi;
			p = p - 2 * dx;
		}
		p = p + 2 * dy;
		x += 1;
	}
}

static void			plot_line_high(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	xi;
	int	p;

	xi = 1;
	dx = point2->v[0] - point1->v[0];
	dy = point2->v[1] - point1->v[1];
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	p = 2 * dx - dy;
	y = point1->v[1];
	x = point1->v[0];
	while (y < point2->v[0])
	{
		plot_pixel(x, y, color, scene);
		if (p > 0)
		{
			x = x + xi;
			p = p - 2 * dy;
		}
		p = p + 2 * dx;
		y += 1;
	}
}

static void			draw_line(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
	if (abs((int)(point2->v[1] - point1->v[1])) <
		abs((int)(point2->v[0] - point1->v[0])))
	{
		if (point1->v[0] > point2->v[0])
			plot_line_low(point2, point1, color, scene);
		else
			plot_line_low(point1, point2, color, scene);
	}
	else
	{
		if (point1->v[1] > point2->v[1])
			plot_line_high(point2, point1, color, scene);
		else
			plot_line_high(point1, point2, color, scene);
	}
}

static void			draw_map(t_scene *scene)
{
	t_vector	*on_screen1;
	t_vector	*on_screen2;
	int			color;
	size_t		i;
	
	color = ft_rgbtoi(*(scene->camera->color));
	i = 0;
	on_screen1 = NULL;
	on_screen2 = NULL;
	while (i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
		{
			if ((on_screen1 = point_to_screen(scene->map->vertices[i], scene)) == NULL ||
				(on_screen2 = point_to_screen(scene->map->vertices[i + 1], scene)) == NULL)
			{
				log_error("Something failed in point_to_screen.", "");
				exit(1);
			}
			draw_line(on_screen1, on_screen2, color, scene);
		}
		// if (i + 1 + scene->map->x < scene->map->vertex_count && 
		// 	((on_screen1 = point_to_screen(scene->map->vertices[i], scene)) == NULL ||
		// 	(on_screen2 =
		// 		point_to_screen(scene->map->vertices[i + 1 + scene->map->x], scene)) == NULL))
		// {
		// 	log_error("Something failed in point_to_screen.", "");
		// 	exit(1);
		// }
		// draw_line(on_screen1, on_screen2, color, scene);
		// if (on_screen1)
		// 	ft_vector_free(on_screen1);
		// if (on_screen2)
		// 	ft_vector_free(on_screen2);
		i++;
	}
}

// static void			draw_axes(t_scene *scene)
// {
// 	t_vector	**vectors;
// 	int			color;

// 	color = ft_rgbtoi(*(scene->camera->color));
// 	if ((vectors = (t_vector**)malloc(sizeof(*vectors) * 6)) == NULL ||
// 		(vectors[0] = ft_vector4_new(-2000, 0, 0)) == NULL ||
// 		(vectors[1] = ft_vector4_new(2000, 0, 0)) == NULL ||
// 		(vectors[2] = ft_vector4_new(0, -2000, 0)) == NULL ||
// 		(vectors[3] = ft_vector4_new(0, 2000, 0)) == NULL ||
// 		(vectors[4] = ft_vector4_new(0, 0, -2000)) == NULL ||
// 		(vectors[5] = ft_vector4_new(0, 0, 2000)) == NULL)
// 		return ;
// 	draw_line(vectors[0], vectors[1], color, scene);
// 	draw_line(vectors[2], vectors[3], color, scene);
// 	draw_line(vectors[4], vectors[5], color, scene);
// 	free(vectors);
// }


void				draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	// draw_axes(scene);
	draw_map(scene);
}