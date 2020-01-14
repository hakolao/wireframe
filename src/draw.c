/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/14 18:21:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector			*screen_pt(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	ft_putstr("Vector: \n");
	ft_putvector(point);
	ft_putstr("Matrix: \n");
	ft_putmatrix(scene->camera->transform);
	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(scene->camera->transform, point, on_screen) == 0)
		return (NULL);
	ft_putstr("Result: \n");
	ft_putvector(on_screen);	
	printf("w: %f\n", on_screen->v[3]);
	// on_screen->v[0] /= on_screen->v[3];
	// on_screen->v[1] /= on_screen->v[3];
	// on_screen->v[2] /= on_screen->v[3];
	// on_screen->v[3] /= on_screen->v[3];
	return (on_screen);
}

static void			draw_map(t_scene *scene)
{
	t_vector	*s1;
	t_vector	*s2;
	int			color;
	size_t		i;
	
	color = ft_rgbtoi(*(scene->camera->color));
	i = -1;
	while (++i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
		{
			if (((s1 = screen_pt(scene->map->vertices[i], scene)) == NULL ||
				(s2 = screen_pt(scene->map->vertices[i + 1], scene)) == NULL) &&
				log_error("Something failed in point_to_screen.", ""))
				exit(1);
			draw_line(s1, s2, color, scene);
		}
		if (i < scene->map->vertex_count - scene->map->x - 1)
		{
			if (((s1 = screen_pt(scene->map->vertices[i], scene)) == NULL ||
				(s2 = screen_pt(scene->map->vertices[i + 1 + scene->map->x], scene)) == NULL) &&
				log_error("Something failed in point_to_screen.", ""))
				exit(1);
			draw_line(s1, s2, color, scene);
		}
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

static void			vector_to_ui(t_scene *scene, char *title, t_vector *v, t_rgb *color, int xpos, int ypos)
{
	char x[50];
	char y[50];
	char z[50];
	char *vectorstr;

	snprintf(x, 50, "%f", v->v[0]);
	snprintf(y, 50, "%f", v->v[1]);
	snprintf(z, 50, "%f", v->v[2]);
	if ((vectorstr = ft_strjoin(x, ", ")) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, y)) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, ", ")) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, z)) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, xpos, ypos, ft_rgbtoi(*color), title);
	mlx_string_put(scene->mlx, scene->mlx_wdw, xpos, ypos + 15, ft_rgbtoi(*color), vectorstr);
}

static void			draw_ui(t_scene *scene)
{
	vector_to_ui(scene, "Camera position:", scene->camera->position, scene->camera->color, 10, 20);
}

void				draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_axes(scene);
	draw_map(scene);
	draw_ui(scene);
}
