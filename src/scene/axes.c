/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:10:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 18:30:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Creates axes array of axis pairs to be used to draw them on screen
*/

t_vector			***axes(int axis_len)
{
	t_vector	***points;
	int			i;

	if ((points = (t_vector***)malloc(sizeof(**points) * 3)) == NULL)
		return (NULL);
	i = 0;
	while (i < 3)
		points[i++] = (t_vector**)malloc(sizeof(*points) * axis_len);
	i = 0;
	while (i < axis_len)
	{
		if (!(points[0][i] = ft_vector4_new(-(axis_len / 2) + i, 0, 0)) ||
			!(points[1][i] = ft_vector4_new(0, -(axis_len / 2) + i, 0)) ||
			!(points[2][i] = ft_vector4_new(0, 0, -(axis_len / 2) + i)))
			return (NULL);
		i++;
	}
	return (points);
}

/*
** Frees axes data from memory
*/

int					free_axes(t_vector ***axes, int len)
{
	int				i;
	int				j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < len)
			ft_vector_free(axes[i][j++]);
		free(axes[i++]);
	}
	free(axes);
	axes = NULL;
	return (0);
}

/*
** Connects axis points using connect_points
*/

static void			connect_axis(t_edge *edge,
					t_vector *point1, t_vector *point2)
{
	edge->point1 = point1;
	edge->point2 = point2;
	connect_points(edge);
}

/*
** Draws axes using connect_points (connect_axis)
*/

void				draw_axes_on_frame(t_scene *scene)
{
	int				color;
	t_edge			*edge;
	int				i;

	color = COLOR(scene->maps[scene->map_index]->col_r / 4,
		scene->maps[scene->map_index]->col_g / 4,
		scene->maps[scene->map_index]->col_b / 4,
		scene->maps[scene->map_index]->col_a / 2);
	if ((edge = (t_edge*)malloc(sizeof(t_edge))) == NULL)
		return ;
	edge->scene = scene;
	edge->color_start = color;
	edge->color_end = color;
	i = 0;
	while (i < scene->axis_len - 1)
	{
		connect_axis(edge, scene->axes[0][i], scene->axes[0][i + 1]);
		connect_axis(edge, scene->axes[1][i], scene->axes[1][i + 1]);
		connect_axis(edge, scene->axes[2][i], scene->axes[2][i + 1]);
		i++;
	}
	free(edge);
}
