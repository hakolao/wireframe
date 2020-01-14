/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/14 14:56:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		re_project(t_scene *scene)
{
	t_matrix	*transform;
	t_matrix	*view;
	t_matrix	*projection;
	int			p;

	projection = NULL;
	p = scene->camera->perspective;
	if (p == PERSPECTIVE)
		projection = ft_perspective_matrix(scene->camera->canvas);
	else if (p == ORTHOGRAPHIC)
		projection = ft_orthographic_matrix(scene->camera->canvas);
	if (projection == NULL ||
		(view =
			ft_view_matrix(scene->camera->position, scene->camera->target, scene->camera->up)) == NULL ||
		(transform =
			cam_transform(scene->map, view, projection)) == NULL)
		return ;
	ft_matrix_free(scene->camera->transform);
	ft_matrix_free(scene->camera->view);
	ft_matrix_free(scene->camera->projection);
	scene->camera->transform = transform;
	scene->camera->projection = projection;
	scene->camera->view = view;
}

static void		re_draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw(scene);
}

static void		zoom(t_scene *scene, int dir)
{
	scene->camera->canvas->angle += dir;
	if (scene->camera->canvas->angle <= 0)
		scene->camera->canvas->angle = 70;
	if (scene->camera->canvas->angle >= 180)
		scene->camera->canvas->angle = 70;
	re_project(scene);
	re_draw(scene);
}

// static void		move_vertical(t_scene *scene, int dir)
// {
// 	scene->camera->position->v[1] += dir;
	// re_project(scene);
// 	re_draw(scene);
// }

// static void		move_horizontal(t_scene *scene, int dir)
// {
// 	scene->camera->position->v[0] += dir;
	// re_project(scene);
// 	re_draw(scene);
// }

static void		rotate_around_z(t_scene *scene)
{
	t_matrix 	*rotation;
	t_matrix	*transform;
	double		angle;

	angle = (M_PI / 180) * 5;
	if ((rotation = ft_matrix_id(4, 4)) == NULL ||
		(transform = ft_matrix_new(4, 4)) == NULL)
		return ;
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 0, 1) = -sin(angle);
	VALUE_AT(rotation, 1, 0) = sin(angle);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	ft_matrix_mul(scene->camera->transform, rotation, transform);
	ft_matrix_free(scene->camera->transform);
	scene->camera->transform = transform;
	re_draw(scene);
}

static void		loop_perspective(t_scene *scene)
{
	scene->camera->perspective++;
	if (scene->camera->perspective > 2)
		scene->camera->perspective = 1;
	re_project(scene);
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
	// if (key == KEY_UP)
	// 	move_vertical(scene, 1);
	// if (key == KEY_DOWN)
	// 	move_vertical(scene, -1);
	// if (key == KEY_LEFT)
	// 	move_horizontal(scene, 1);
	if (key == KEY_RIGHT)
		rotate_around_z(scene);
	if (key == KEY_P)
		loop_perspective(scene);
	return (0);
}
