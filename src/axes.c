/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:10:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 19:16:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void			free_axes(t_vector ***points)
{
	int				i;
	int				j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 100)
			ft_vector_free(points[i][j++]);
		free(points[i++]);
	}
}

static void			connect_axis(t_line_connect *line_connect,
					t_vector *point1, t_vector *point2)
{
	line_connect->point1 = point1;
	line_connect->point2 = point2;
	connect_points(line_connect);
}

void				draw_axes(t_scene *scene)
{
	int				color;
	t_vector		***points;
	t_line_connect	*line_connect;
	int				i;

	color = ((100 & 255) << 16) | ((100 & 255) << 8 | (100 & 255));
	if ((points = axes()) == NULL ||
		(line_connect = malloc(sizeof(t_line_connect))) == NULL)
		return ;
	line_connect->scene = scene;
	line_connect->color_start = color;
	line_connect->color_end = color;
	i = 0;
	while (i < 100 - 1)
	{
		connect_axis(line_connect, points[0][i], points[0][i + 1]);
		connect_axis(line_connect, points[1][i], points[1][i + 1]);
		connect_axis(line_connect, points[2][i], points[2][i + 1]);
		i++;
	}
	free_axes(points);
	free(line_connect);
}
