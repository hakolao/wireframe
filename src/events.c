/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/15 19:47:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void				set_transform(t_scene *scene)
{
	t_matrix	*transform;

	if ((transform = cam_transform(scene->camera)) == NULL)
		return ;
	ft_matrix_free(scene->camera->transform);
	scene->camera->transform = transform;
}

static void		re_draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw(scene);
}

static void		zoom(t_scene *scene, int dir)
{
	t_matrix	*projection;

	scene->camera->canvas->angle += dir;
	if (scene->camera->canvas->angle <= 0)
		scene->camera->canvas->angle = 70;
	if (scene->camera->canvas->angle >= 180)
		scene->camera->canvas->angle = 70;
	if ((projection =
			scene->camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(scene->camera->canvas) :
			ft_orthographic_matrix(scene->camera->canvas)) == NULL)
		return ;
	ft_matrix_free(scene->camera->projection);
	scene->camera->projection = projection;
	set_transform(scene);
	re_draw(scene);
}

void		apply_matrix_on_map(t_matrix *m, t_map *map)
{
	size_t		i;
	t_vector	*vec;

	i = 0;
	while (i < map->vertex_count)
	{
		vec = ft_vector_new(4);
		ft_matrix_mul_vector(m, map->vertices[i], vec);
		vec->v[3] = 1;
		ft_vector_free(map->vertices[i]);
		map->vertices[i] = vec;
		i++;
	}
}

static void		rotate_around_z(t_scene *scene)
{
	t_matrix 	*rotation;
	double		angle;


	angle = (M_PI / 180) * 5;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return ;
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 0, 1) = -sin(angle);
	VALUE_AT(rotation, 1, 0) = sin(angle);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
}

static void		rotate_around_y(t_scene *scene)
{
	t_matrix 	*rotation;
	double		angle;
	
	angle = (M_PI / 180) * 5;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return ;
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 2, 0) = sin(angle);
	VALUE_AT(rotation, 0, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
}

static void		rotate_around_x(t_scene *scene)
{
	t_matrix 	*rotation;
	double		angle;
	
	angle = (M_PI / 180) * 5;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return ;
	VALUE_AT(rotation, 1, 1) = cos(angle);
	VALUE_AT(rotation, 1, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 1) = sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
}

static void		loop_perspective(t_scene *scene)
{
	t_matrix	*projection;

	scene->camera->perspective++;
	if (scene->camera->perspective > 2)
		scene->camera->perspective = PERSPECTIVE;
	if ((projection =
			scene->camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(scene->camera->canvas) :
			ft_orthographic_matrix(scene->camera->canvas)) == NULL)
		return ;
	ft_matrix_free(scene->camera->projection);
	scene->camera->projection = projection;
	re_draw(scene);
}

int				handle_key_events(int key, void *param)
{
	t_scene	*scene;

	ft_putnbr(key);
	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	if (key == KEY_W)
		zoom(scene, -1);
	if (key == KEY_S)
		zoom(scene, 1);
	if (key == KEY_LEFT)
		rotate_around_y(scene);
	if (key == KEY_RIGHT)
		rotate_around_z(scene);
	if (key == KEY_UP)
		rotate_around_x(scene);
	if (key == KEY_P)
		loop_perspective(scene);
	return (0);
}
