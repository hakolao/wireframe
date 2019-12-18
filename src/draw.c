/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 19:03:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector		*point_to_screen(t_vector *point, t_scene *scene)
{
	t_matrix		*res_mat;

	if ((res_mat = ft_matrix_mul(scene->camera->projection, scene->camera->view_matrix)) == NULL)
		return (NULL);
	return (ft_matrix_mul_vector(res_mat, point));
}

static void		draw_pixel(void *mlx, void *mlx_wdw, t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;
	int			color;
	double		xin_minmax[2];
	double		xout_minmax[2];
	double		yin_minmax[2];
	double		yout_minmax[2];
	
	xin_minmax[0] = 0;
	xin_minmax[1] = scene->map->x_max;
	xout_minmax[0] = 0;
	xout_minmax[1] = WINDOW_WIDTH;
	yin_minmax[0] = 0;
	yin_minmax[1] = scene->map->y_max;
	yout_minmax[0] = 0;
	yout_minmax[1] = WINDOW_HEIGHT;
	if ((on_screen = point_to_screen(point, scene)) == NULL)
	{
		log_error("Something failed in point_to_screen.", "");
		exit(1);
	}
	// ft_putvector(on_screen);
	color = ft_rgbtoi(scene->camera->color->r,
						scene->camera->color->g,
						scene->camera->color->b);
	mlx_pixel_put(mlx, mlx_wdw,
				ft_lmap_double(on_screen->v[0], xin_minmax, xout_minmax) + WINDOW_WIDTH / 2, 
				ft_lmap_double(on_screen->v[1], yin_minmax, yout_minmax) + WINDOW_HEIGHT / 2,
				color);
}

void	draw(void *mlx, void *mlx_wdw, t_scene *scene)
{
	t_list	*vertex;

	vertex = scene->map->vertices;
	while (vertex)
	{
		draw_pixel(mlx, mlx_wdw, (t_vector*)vertex->content, scene);
		vertex = vertex->next;
	}
}