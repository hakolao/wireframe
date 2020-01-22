/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:44:31 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 15:28:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_transform(t_camera *camera)
{
	t_matrix	*transform;

	if ((transform = cam_transform(camera)) == NULL)
		return ;
	ft_matrix_free(camera->transform);
	camera->transform = transform;
}

int				turn_camera(t_camera *camera, double pitch, double yaw)
{
	t_matrix	*view;
	double		new_pitch;
	double		new_yaw;

	new_pitch = camera->pitch;
	new_yaw = camera->yaw;
	new_yaw += yaw;
	if (new_yaw >= 359)
		new_yaw = 1;
	new_pitch += pitch;
	if (new_pitch > 89)
		new_pitch = 89;
	if (new_pitch < -89)
		new_pitch = -89;
	if ((view =
		ft_fps_cam(camera->position, new_pitch, new_yaw)) == NULL)
		return (0);
	camera->pitch = new_pitch;
	camera->yaw = new_yaw;
	ft_matrix_free(camera->view);
	camera->view = view;
	set_transform(camera);
	return (1);
}

int				move_camera(t_camera *camera, double amount)
{
	t_matrix	*view;
	t_vector	*forward;
	t_vector	*new_pos;

	if ((forward = ft_vector4_new(
			sin(camera->yaw) * cos(camera->pitch),
			-sin(camera->pitch),
			cos(camera->pitch) * cos(camera->yaw))) == NULL ||
		(new_pos = ft_vector_new(4)) == NULL ||
		(amount > 0 ? ft_vector_add(camera->position, forward, new_pos) :
			ft_vector_sub(camera->position, forward, new_pos)) == FALSE ||
		(view = ft_fps_cam(new_pos, camera->pitch, camera->yaw)) == NULL)
		return (0);
	ft_vector_free(forward);
	camera->position = new_pos;
	ft_matrix_free(camera->view);
	camera->view = view;
	set_transform(camera);
	return (1);
}

int				zoom(t_camera *camera, int dir)
{
	t_matrix	*projection;

	camera->canvas->angle += dir;
	if (camera->canvas->angle < 1)
		camera->canvas->angle = 1;
	if (camera->canvas->angle > 179)
		camera->canvas->angle = 179;
	if ((projection =
			camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(camera->canvas) :
			ft_orthographic_matrix(camera->canvas)) == NULL)
		return (0);
	ft_matrix_free(camera->projection);
	camera->projection = projection;
	set_transform(camera);
	return (1);
}

int				loop_perspective(t_camera *camera)
{
	t_matrix	*projection;

	camera->perspective++;
	if (camera->perspective > 2)
		camera->perspective = PERSPECTIVE;
	if ((projection =
			camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(camera->canvas) :
			ft_orthographic_matrix(camera->canvas)) == NULL)
		return (0);
	ft_matrix_free(camera->projection);
	camera->projection = projection;
	set_transform(camera);
	return (1);
}
