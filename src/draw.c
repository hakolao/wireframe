/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 21:26:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector		*point_to_screen(t_vector *point, t_scene *scene)
{
	return (ft_matrix_mul_vector(scene->camera->transform, point));
}

static void		draw_pixel(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;
	int			color;

	if ((on_screen = point_to_screen(point, scene)) == NULL)
	{
		log_error("Something failed in point_to_screen.", "");
		exit(1);
	}
	// ft_putvector(on_screen);
	color = ft_rgbtoi(*(scene->camera->color));
	mlx_pixel_put(scene->mlx, scene->mlx_wdw,
				on_screen->v[0] + WINDOW_WIDTH / 2, 
				on_screen->v[1] + WINDOW_HEIGHT / 2,
				color);
}

void	draw(t_scene *scene)
{
	t_list		*vertex;
	t_matrix	*transform;
	t_matrix	*model;

	if ((model = ft_matrix_id(4, 4)) == NULL)
		return ;
	VALUE_AT(model, 0, 0) = scene->map->scale;
	VALUE_AT(model, 1, 1) = scene->map->scale;
	VALUE_AT(model, 2, 2) = scene->map->scale;
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
	vertex = scene->map->vertices;
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	while (vertex)
	{
		draw_pixel((t_vector*)vertex->content, scene);
		vertex = vertex->next;
	}
}