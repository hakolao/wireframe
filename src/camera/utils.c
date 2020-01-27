/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:44:31 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 12:14:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Turn camera by pitch & yaw (angles). Pitch is vertical angle movement.
** Yaw is horizontal angle movement
*/

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

/*
** Forward camera movement by given amount (speed)
*/

int				move_camera_forward(t_camera *camera, double amount)
{
	t_matrix	*view;
	t_vector	*forward;
	t_vector	*new_pos;

	if ((forward = ft_vector4_new(
			VALUE_AT(camera->view, 2, 0),
			VALUE_AT(camera->view, 2, 1),
			VALUE_AT(camera->view, 2, 2))) == NULL ||
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

/*
** Sideways camera movement by given amount (speed)
*/

int				strafe_camera(t_camera *camera, double amount)
{
	t_matrix	*view;
	t_vector	*sideways;
	t_vector	*new_pos;

	if ((sideways = ft_vector4_new(
			VALUE_AT(camera->view, 0, 0),
			VALUE_AT(camera->view, 0, 1),
			VALUE_AT(camera->view, 0, 2))) == NULL ||
		(new_pos = ft_vector_new(4)) == NULL ||
		(amount > 0 ? ft_vector_add(camera->position, sideways, new_pos) :
			ft_vector_sub(camera->position, sideways, new_pos)) == FALSE ||
		(view = ft_fps_cam(new_pos, camera->pitch, camera->yaw)) == NULL)
		return (0);
	ft_vector_free(sideways);
	camera->position = new_pos;
	ft_matrix_free(camera->view);
	camera->view = view;
	set_transform(camera);
	return (1);
}

/*
** Zoom changes camera's canvas' angles (field of view)
** to bring viewed data closer (appears closer)
*/

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

/*
** Utility function to loop camera perspective
*/

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
