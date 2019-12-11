/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 20:33:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_matrix4	rot_around_x(double angle)
{
	t_matrix4	mat;
	
	mat = identity_matrix();
	mat.vecs[1].vec[1] = cos(angle); 
	mat.vecs[2].vec[1] = -sin(angle); 
	mat.vecs[1].vec[2] = sin(angle); 
	mat.vecs[2].vec[2] = cos(angle);
	return (mat);
}

t_matrix4	rot_around_y(double angle)
{
	t_matrix4	mat;
	
	mat = identity_matrix();
	mat.vecs[0].vec[0] = cos(angle); 
	mat.vecs[2].vec[0] = sin(angle); 
	mat.vecs[0].vec[2] = -sin(angle); 
	mat.vecs[2].vec[2] = cos(angle);
	return (mat);
}

t_matrix4	rot_around_z(double angle)
{
	t_matrix4	mat;
	
	mat = identity_matrix();
	mat.vecs[0].vec[0] = cos(angle); 
	mat.vecs[1].vec[0] = -sin(angle); 
	mat.vecs[0].vec[1] = sin(angle); 
	mat.vecs[1].vec[1] = cos(angle);
	return (mat);
}

t_vec4		point_to_screen(t_point *point, t_scene *scene)
{
	t_vec4		vec;
	t_matrix4	rot;

	vec.vec[0] = point->x;
	vec.vec[1] = point->y;
	vec.vec[2] = point->z;
	vec.vec[3] = 1;
	rot = rot_around_y(0.4);
	return (vec_mult_by_matrix(vec, matrix_mul(scene->camera->view_matrix, rot)));
}

static void		draw_pixel(void *mlx, void *mlx_wdw, t_point *point, t_scene *scene)
{
	t_vec4		s;
	int			color;

	s = point_to_screen(point, scene);
	printf("screen x: %d, screen y: %d, screen z: %d\n", (int)s.vec[0], (int)s.vec[1], (int)s.vec[2]);
	color = ft_rgbtoi(scene->camera->color->r,
						scene->camera->color->g,
						scene->camera->color->b);
	mlx_pixel_put(mlx, mlx_wdw, 
				WINDOW_WIDTH / 2 + s.vec[0] - scene->map->x_max / 2 * scene->camera->zoom, 
				WINDOW_HEIGHT / 2 + s.vec[1] - scene->map->y_max / 2 * scene->camera->zoom,
				color);
}

void	draw(void *mlx, void *mlx_wdw, t_scene *scene)
{
	t_list	*vertex;

	vertex = scene->map->vertices;
	while (vertex)
	{
		draw_pixel(mlx, mlx_wdw, (t_point*)vertex->content, scene);
		vertex = vertex->next;
	}
}