/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 18:13:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	move_camera(t_camera *camera, t_vector *direction, double speed)
{
	t_matrix	*view;
	t_vector	*position;

	position = camera->position;
	ft_vector_scale(direction, speed);
	if ((position = ft_vector_add(position, direction)) == NULL ||
		(view = ft_view_matrix(position, camera->target, camera->up)) == NULL)
		return ;
	ft_vector_free(camera->position);
	ft_matrix_free(camera->view);
	camera->position = position;
	camera->view = view;
}

void	move_forward(t_scene *scene)
{
	t_vector	*forward;

	ft_putstr("moving forward\n");
	if ((forward = ft_vector_forward(
					scene->camera->position, scene->camera->target)) == NULL)
		return ;
	move_camera(scene->camera, forward, MOVE_SPEED);
	draw(scene);
}

int		handle_key_events(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == KEY_ESC)
		exit(0);
	// ft_putnbr(key);
	if (key == KEY_W)
		move_forward(scene);
	return (0);
}