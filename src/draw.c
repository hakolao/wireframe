/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 17:15:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector		*point_to_screen(t_vector *point, t_scene *scene)
{
	t_matrix		*projection;
	t_matrix		*res_mat;

	if ((projection = ft_orthographic_matrix(scene->camera->canvas)) == NULL)
		return (NULL);
	if ((res_mat = ft_matrix_mul(projection, scene->camera->view_matrix)) == NULL)
		return (NULL);
	return (ft_matrix_mul_vector(res_mat, point));
}

static void		draw_pixel(void *mlx, void *mlx_wdw, t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;
	int			color;

	if ((on_screen = point_to_screen(point, scene)) == NULL)
	{
		log_error("Something failed in point_to_screen.", "");
		exit(1);
	}
	printf("screen x: %d, screen y: %d\n", 
			(int)on_screen->v[0], (int)on_screen->v[1]);
	color = ft_rgbtoi(scene->camera->color->r,
						scene->camera->color->g,
						scene->camera->color->b);
	mlx_pixel_put(mlx, mlx_wdw,
				on_screen->v[0], 
				on_screen->v[1],
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