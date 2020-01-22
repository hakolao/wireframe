/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 16:41:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_vector		***axes(void)
{
	t_vector	***points;
	int			i;

	if ((points = (t_vector***)malloc(sizeof(**points) * 3)) == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
		points[i++] = (t_vector**)malloc(sizeof(*points) * 100);
	i = 0;
	while (i < 100)
	{
		if ((points[0][i] = ft_vector4_new(-50 + i, 0, 0)) == NULL ||
			(points[1][i] = ft_vector4_new(0, -50 + i, 0)) == NULL ||
			(points[2][i] = ft_vector4_new(0, 0, -50 + i)) == NULL)
			return (NULL);
		i++;
	}
	return (points);
}

static void			draw_axes(t_scene *scene)
{
	int			color;
	t_vector	***points;
	int			i;

	color = ((100 & 255) << 16) | ((100 & 255) << 8 | (100 & 255));
	if ((points = axes()) == NULL)
		return ;
	i = 0;
	while (i < 100 - 1)
	{
		connect_points(points[0][i], points[0][i + 1], scene, color);
		connect_points(points[1][i], points[1][i + 1], scene, color);
		connect_points(points[2][i], points[2][i + 1], scene, color);
		ft_vector_free(points[0][i]);
		ft_vector_free(points[1][i]);
		ft_vector_free(points[2][i]);
		i++;
	}
	ft_vector_free(points[0][i]);
	ft_vector_free(points[1][i]);
	ft_vector_free(points[2][i]);
	i = 0;
	while (i < 3)
		free(points[i++]);
}

static void			draw_map(t_scene *scene)
{
	int			color;
	size_t		i;

	color = ft_rgbtoi(*(scene->map->color));
	i = -1;
	while (++i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
			connect_points(
				scene->map->vertices[i],
				scene->map->vertices[i + 1],
				scene,
				color);
		if (i < scene->map->vertex_count - scene->map->x - 1)
			connect_points(scene->map->vertices[i],
				scene->map->vertices[i + 1 + scene->map->x],
				scene,
				color);
	}
}

int					draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_map(scene);
	draw_axes(scene);
	draw_ui(scene);
	return (1);
}
