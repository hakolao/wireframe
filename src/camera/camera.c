/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:54:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:09:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Creates a canvas used for camera's projection matrices
*/

static t_canvas		*new_canvas(void)
{
	t_canvas	*c;

	if ((c = (t_canvas*)malloc(sizeof(*c))) == NULL)
		return (NULL);
	c->width = ASPECT_RATIO * 25;
	c->height = 25;
	c->near = 0.1;
	c->far = 10;
	c->angle = 70;
	return (c);
}

/*
** Frees camera struct so camera can be reset
*/

int					camera_free(t_camera *camera)
{
	ft_matrix_free(camera->projection);
	ft_matrix_free(camera->view);
	ft_matrix_free(camera->transform);
	ft_matrix_free(camera->unit_scale);
	ft_vector_free(camera->position);
	ft_vector_free(camera->init_position);
	ft_vector_free(camera->up);
	free(camera->canvas);
	free(camera);
	return (0);
}

/*
** Sets camera transform (This needs to be set whenever
** camera variables are changed)
*/

int					set_transform(t_camera *camera)
{
	t_matrix	transform;

	transform = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	if (!cam_transform(camera, &transform))
		return (0);
	return (ft_matrix_set_vals(camera->transform, transform.m, 16));
}

/*
** Calculates camera's transform
*/

int					cam_transform(t_camera *camera, t_matrix *res)
{
	t_matrix	tmp;

	tmp = (t_matrix){.m = (double[16]){0}, .cols = 4, .rows = 4};
	if (ft_matrix_mul(camera->projection, camera->view, &tmp) == FALSE ||
		ft_matrix_mul(camera->unit_scale, &tmp, res) == FALSE)
		return (FALSE);
	return (TRUE);
}

/*
** Creates a new fps camera
*/

t_camera			*new_camera(t_vector *position, t_vector *up, t_map *map)
{
	t_camera	*camera;
	double		pitch;
	double		yaw;

	pitch = 0;
	yaw = 0;
	if (position == NULL || map->center == NULL || up == NULL ||
		(camera = (t_camera*)malloc(sizeof(*camera))) == NULL ||
		(camera->canvas = new_canvas()) == NULL ||
		(camera->view = ft_matrix_new(4, 4)) == NULL ||
		!ft_fps_cam(position, pitch, yaw, camera->view) ||
		(camera->projection = ft_matrix_new(4, 4)) == NULL ||
		!ft_perspective_matrix(camera->canvas, camera->projection) ||
		!(camera->unit_scale = ft_scale_matrix_xyz(SCALE, SCALE, SCALE)) ||
		!(camera->transform = ft_matrix_new(4, 4)) || !set_transform(camera) ||
		(camera->init_position = ft_vector4_new(position->v[0],
			position->v[1], position->v[2])) == NULL ||
		(camera->position = ft_vector4_new(position->v[0],
			position->v[1], position->v[2])) == NULL ||
		(camera->up = ft_vector4_new(up->v[0], up->v[1], up->v[2])) == NULL)
		return (NULL);
	camera->pitch = pitch;
	camera->yaw = yaw;
	camera->perspective = PERSPECTIVE;
	return (camera);
}
