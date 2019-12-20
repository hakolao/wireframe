/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/20 16:12:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector			*point_to_screen(t_vector *point, t_scene *scene)
{
	return (ft_matrix_mul_vector(scene->camera->transform, point));
}

static void			draw_line(t_vector *point1, t_vector *point2, int color, t_scene *scene)
{
    int dx;
	int	dy;
	int	p;
	int	x;
	int	y;
 
	dx = point2->v[0] - point1->v[0];
	dy = point2->v[1] - point1->v[1];
	x = point1->v[0];
	y = point1->v[1];
	p = 2 * dy - dx;
 
	while (x < point2->v[0])
	{
		if ( p >= 0)
		{
			mlx_pixel_put(scene->mlx, scene->mlx_wdw,
				x + WINDOW_WIDTH / 2, y + WINDOW_HEIGHT / 2, color);
			y = y+1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			mlx_pixel_put(scene->mlx, scene->mlx_wdw,
				x + WINDOW_WIDTH / 2, y + WINDOW_HEIGHT / 2, color);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

static t_matrix		*model_matrix(t_scene *scene)
{
	t_matrix	*model;

	if ((model = ft_matrix_id(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(model, 0, 0) = scene->map->scale;
	VALUE_AT(model, 1, 1) = scene->map->scale;
	VALUE_AT(model, 2, 2) = scene->map->scale;
	return (model);
}

static void			draw_map(t_scene *scene)
{
	t_vector	*on_screen1;
	t_vector	*on_screen2;
	int			color;
	size_t		i;
	
	color = ft_rgbtoi(*(scene->camera->color));
	i = 0;
	while (i < scene->map->vertex_count)
	{
		if ((i + 1) % (int)(scene->map->x_max) != 0)
		{
			if ((on_screen1 = point_to_screen(scene->map->vertices[i], scene)) == NULL ||
			(on_screen2 = point_to_screen(scene->map->vertices[i + 1], scene)) == NULL)
			{
				log_error("Something failed in point_to_screen.", "");
				exit(1);
			}
		}
		draw_line(on_screen1, on_screen2, color, scene);
		if ((i / scene->map->x_max) != scene->map->y_max)
		{
			if ((on_screen1 = point_to_screen(scene->map->vertices[i], scene)) == NULL ||
			(on_screen2 = point_to_screen(
				scene->map->vertices[i + (int)scene->map->x_max],
				scene)) == NULL)
			{
				log_error("Something failed in point_to_screen.", "");
				exit(1);
			}
		}
		draw_line(on_screen1, on_screen2, color, scene);
		i++;
	}
}

static void			draw_axes(t_scene *scene)
{
	t_vector	**vectors;
	int			color;

	color = ft_rgbtoi(*(scene->camera->color));
	if ((vectors = (t_vector**)malloc(sizeof(*vectors) * 6)) == NULL ||
		(vectors[0] = ft_vector4_new(-2000, 0, 0)) == NULL ||
		(vectors[1] = ft_vector4_new(2000, 0, 0)) == NULL ||
		(vectors[2] = ft_vector4_new(0, -2000, 0)) == NULL ||
		(vectors[3] = ft_vector4_new(0, 2000, 0)) == NULL ||
		(vectors[4] = ft_vector4_new(0, 0, -2000)) == NULL ||
		(vectors[5] = ft_vector4_new(0, 0, 2000)) == NULL)
		return ;
	draw_line(vectors[0], vectors[1], color, scene);
	draw_line(vectors[2], vectors[3], color, scene);
	draw_line(vectors[4], vectors[5], color, scene);
	free(vectors);
}

static void			set_transform(t_scene *scene)
{
	t_matrix	*transform;
	t_matrix	*model;

	if ((model = model_matrix(scene)) == NULL)
		return ;
	if ((transform = ft_matrix_mul(scene->camera->projection, scene->camera->view)) == NULL)
		return ;
	if ((transform = ft_matrix_mul(transform, model)) == NULL)
		return ;
	if (scene->camera->transform)
	{
		ft_matrix_free(model);
		ft_matrix_free(scene->camera->transform);
	}
	scene->camera->transform = transform;
}

void				draw(t_scene *scene)
{
	set_transform(scene);
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_axes(scene);
	draw_map(scene);
}