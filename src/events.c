/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/17 16:03:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		set_transform(t_scene *scene)
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

static int		zoom(t_scene *scene, int dir)
{
	t_matrix	*projection;

	scene->camera->canvas->angle += dir;
	if (scene->camera->canvas->angle < 1)
		scene->camera->canvas->angle = 1;
	if (scene->camera->canvas->angle > 179)
		scene->camera->canvas->angle = 179;
	if ((projection =
			scene->camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(scene->camera->canvas) :
			ft_orthographic_matrix(scene->camera->canvas)) == NULL)
		return (0);
	ft_matrix_free(scene->camera->projection);
	scene->camera->projection = projection;
	set_transform(scene);
	re_draw(scene);
	return (1);
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

int		rotate_around_z(t_scene *scene, int amount)
{
	t_matrix 	*rotation;
	double		angle;


	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (0);
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 0, 1) = -sin(angle);
	VALUE_AT(rotation, 1, 0) = sin(angle);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
	return (1);
}

int		rotate_around_y(t_scene *scene, int amount)
{
	t_matrix 	*rotation;
	double		angle;
	
	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (0);
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 2, 0) = sin(angle);
	VALUE_AT(rotation, 0, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
	return (1);
}

int		rotate_around_x(t_scene *scene, int amount)
{
	t_matrix 	*rotation;
	double		angle;
	
	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (0);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	VALUE_AT(rotation, 1, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 1) = sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	apply_matrix_on_map(rotation, scene->map);
	ft_matrix_free(rotation);
	re_draw(scene);
	return (1);
}

int		loop_perspective(t_scene *scene)
{
	t_matrix	*projection;

	scene->camera->perspective++;
	if (scene->camera->perspective > 2)
		scene->camera->perspective = PERSPECTIVE;
	if ((projection =
			scene->camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(scene->camera->canvas) :
			ft_orthographic_matrix(scene->camera->canvas)) == NULL)
		return (0);
	ft_matrix_free(scene->camera->projection);
	scene->camera->projection = projection;
	re_draw(scene);
	return (1);
}

static int		turn_camera(t_scene *scene, double pitch, double yaw)
{
	t_matrix *view;
	double		new_pitch;
	double		new_yaw;
	
	new_pitch = scene->camera->pitch;
	new_yaw = scene->camera->yaw;
	new_yaw += yaw;
	if (new_yaw > 360)
		new_yaw = 1;
	new_pitch += pitch;
	if (new_pitch > 90)
		new_pitch = 90;
	if (new_pitch < -90)
		new_pitch = -90;
	if ((view = ft_fps_cam(scene->camera->position, new_pitch, new_yaw)) == NULL)
		return (0);
	scene->camera->pitch = new_pitch;
	scene->camera->yaw = new_yaw;
	ft_matrix_free(scene->camera->view);
	scene->camera->view = view;
	set_transform(scene);
	re_draw(scene);
	return (1);
}

static int		move_camera_z(t_scene *scene, double amount)
{
	t_matrix 	*view;
	t_vector	*new_pos;
	
	if ((new_pos = ft_vector4_new(
					scene->camera->position->v[0],
					scene->camera->position->v[1],
					scene->camera->position->v[2] + amount)) == NULL ||
		(view = ft_fps_cam(scene->camera->position,
						scene->camera->pitch,
							scene->camera->yaw)) == NULL)
		return (0);
	scene->camera->position = new_pos;
	ft_matrix_free(scene->camera->view);
	scene->camera->view = view;
	set_transform(scene);
	re_draw(scene);
	return (1);
}

static int		move_camera_x(t_scene *scene, double amount)
{
	t_matrix 	*view;
	t_vector	*new_pos;
	
	if ((new_pos = ft_vector4_new(
					scene->camera->position->v[0] + amount,
					scene->camera->position->v[1],
					scene->camera->position->v[2])) == NULL ||
		(view = ft_fps_cam(scene->camera->position,
						scene->camera->pitch,
							scene->camera->yaw)) == NULL)
		return (0);
	scene->camera->position = new_pos;
	ft_matrix_free(scene->camera->view);
	scene->camera->view = view;
	set_transform(scene);
	re_draw(scene);
	return (1);
}

int				handle_key_events(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	return ((key == KEY_W && rotate_around_x(scene, 3)) ||
		(key == KEY_S && rotate_around_x(scene, -3)) ||
		(key == KEY_A && rotate_around_y(scene, 3)) ||
		(key == KEY_D && rotate_around_y(scene, -3)) ||
		(key == KEY_Q && rotate_around_z(scene, -3)) ||
		(key == KEY_E && rotate_around_z(scene, 3)) ||
		(key == KEY_UP && move_camera_z(scene, 1)) ||
		(key == KEY_DOWN && move_camera_z(scene, -1)) ||
		(key == KEY_RIGHT && move_camera_x(scene, 1)) ||
		(key == KEY_LEFT && move_camera_x(scene, -1)) ||
		(key == KEY_NUM_4 && turn_camera(scene, 0, -2)) ||
		(key == KEY_NUM_6 && turn_camera(scene, 0, 2)) ||
		(key == KEY_NUM_8 && turn_camera(scene, 2, 0)) ||
		(key == KEY_NUM_2 && turn_camera(scene, -2, 0)) ||
		(key == KEY_P && loop_perspective(scene)) ||
		(key == KEY_1 && zoom(scene, 1)) ||
		(key == KEY_2 && zoom(scene, -1)));
}
