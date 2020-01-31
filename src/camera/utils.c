/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:44:31 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/31 16:00:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Turn camera by pitch & yaw (angles). Pitch is vertical angle movement.
** Yaw is horizontal angle movement
*/

int				turn_camera(t_camera *camera, double pitch, double yaw)
{
	t_matrix	view;
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
	view = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	if (!ft_fps_cam(camera->position, new_pitch, new_yaw, &view))
		return (0);
	camera->pitch = new_pitch;
	camera->yaw = new_yaw;
	return (ft_matrix_set_vals(camera->view, view.m, 16) &&
			set_transform(camera));
}

/*
** Forward camera movement by given amount (speed)
*/

int				move_camera_forward(t_camera *camera, double amount)
{
	t_matrix	view;
	t_vector	forward;
	t_vector	new_pos;

	view = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	forward = (t_vector){.v = (double[4]){VALUE_AT(camera->view, 2, 0),
						VALUE_AT(camera->view, 2, 1),
						VALUE_AT(camera->view, 2, 2), 1}, .size = 4};
	new_pos = (t_vector){.v = (double[4]){0}, .size = 4};
	if ((amount > 0 ? ft_vector_add(camera->position, &forward, &new_pos) :
			ft_vector_sub(camera->position, &forward, &new_pos)) == FALSE ||
		ft_fps_cam(&new_pos, camera->pitch, camera->yaw, &view) == FALSE)
		return (0);
	return (ft_vector_set_vals(camera->position, new_pos.v, 4) &&
			ft_matrix_set_vals(camera->view, view.m, 16) &&
			set_transform(camera));
}

/*
** Sideways camera movement by given amount (speed)
*/

int				strafe_camera(t_camera *camera, double amount)
{
	t_matrix	view;
	t_vector	sideways;
	t_vector	new_pos;

	view = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	sideways = (t_vector){.v = (double[4]){VALUE_AT(camera->view, 0, 0),
						VALUE_AT(camera->view, 0, 1),
						VALUE_AT(camera->view, 0, 2), 1}, .size = 4};
	new_pos = (t_vector){.v = (double[4]){0}, .size = 4};
	if ((amount > 0 ? ft_vector_add(camera->position, &sideways, &new_pos) :
			ft_vector_sub(camera->position, &sideways, &new_pos)) == FALSE ||
		ft_fps_cam(&new_pos, camera->pitch, camera->yaw, &view) == FALSE)
		return (0);
	return (ft_vector_set_vals(camera->position, new_pos.v, 4) &&
			ft_matrix_set_vals(camera->view, view.m, 16) &&
			set_transform(camera));
}

/*
** Zoom changes camera's canvas' angles (field of view)
** to bring viewed data closer (appears closer)
*/

int				zoom(t_camera *camera, int dir)
{
	camera->canvas->angle += dir;
	if (camera->canvas->angle < 1)
		camera->canvas->angle = 1;
	if (camera->canvas->angle > 179)
		camera->canvas->angle = 179;
	return ((camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(camera->canvas, camera->projection) :
			ft_orthographic_matrix(camera->canvas, camera->projection)) &&
			set_transform(camera));
}

/*
** Utility function to loop camera perspective
*/

int				loop_perspective(t_camera *camera)
{
	camera->perspective++;
	if (camera->perspective > 2)
		camera->perspective = PERSPECTIVE;
	return ((camera->perspective == PERSPECTIVE ?
			ft_perspective_matrix(camera->canvas, camera->projection) :
			ft_orthographic_matrix(camera->canvas, camera->projection)) &&
			set_transform(camera));
}
