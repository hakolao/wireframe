/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/08 13:20:20 by ohakola          ###   ########.fr       */
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
			ft_vector_free(on_screen1);
			ft_vector_free(on_screen2);
		}
		if (i < scene->map->vertex_count - scene->map->x - 1)
		{
			if ((on_screen1 = point_to_screen(scene->map->vertices[i], scene)) == NULL ||
				(on_screen2 =
					point_to_screen(scene->map->vertices[i + 1 + scene->map->x], scene)) == NULL)
			{
				log_error("Something failed in point_to_screen.", "");
				exit(1);
			}
			draw_line(on_screen1, on_screen2, color, scene);
			ft_vector_free(on_screen1);
			ft_vector_free(on_screen2);
		}
		i++;
	}
}

static void			draw_axes(t_scene *scene)
{
	t_vector	**vectors;
	t_rgb		rgb;
	int			color;

	rgb.r = 255;
	rgb.g = 0;
	rgb.b = 0;
	color = ft_rgbtoi(rgb);
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


void				draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_axes(scene);
	draw_map(scene);
}