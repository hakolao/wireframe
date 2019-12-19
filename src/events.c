/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 19:39:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	validate_position(t_vector *position)
{
	if (position->v[0] < X_MIN_LIMIT || position->v[0] > X_MAX_LIMIT ||
		position->v[1] < Y_MIN_LIMIT || position->v[1] > Y_MAX_LIMIT ||
		position->v[2] < Z_MIN_LIMIT || position->v[2] > Z_MAX_LIMIT)
	{
		position->v[0] = X_POS_INIT;
		position->v[1] = Y_POS_INIT;
		position->v[2] = Z_POS_INIT;
	}
	position->v[3] = 1;
}

void	move_camera(t_camera *camera, t_vector *direction, double speed)
{
	t_matrix	*view;
	t_vector	*position;
	double		vals[4];

	position = camera->position;
	vals[0] = direction->v[0] * speed;
	vals[1] = direction->v[1] * speed;
	vals[2] = direction->v[2] * speed;
	vals[3] = 1;
	ft_vector_set_vals(direction, vals, 4);
	if ((position = ft_vector_add(position, direction)) == NULL)
		return ;
	validate_position(position);
	if ((view = ft_view_matrix(position, camera->target, camera->up)) == NULL)
		return ;
	ft_vector_free(camera->position);
	ft_matrix_free(camera->view);
	camera->position = position;
	camera->view = view;
}

void	move_forward(t_scene *scene)
{
	t_vector	*towards;

	ft_putstr("moving forward\n");
	if ((towards = ft_vector_forward(
					scene->camera->position, scene->camera->target)) == NULL)
		return ;
	move_camera(scene->camera, towards, MOVE_SPEED);
	ft_putvector(scene->camera->position);
	draw(scene);
}

int		handle_key_events(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	// ft_putnbr(key);
	if (key == KEY_W)
		move_forward(scene);
	return (0);
}