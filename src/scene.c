/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 16:23:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

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

void				set_transform(t_camera *camera)
{
	t_matrix	*transform;

	if ((transform = cam_transform(camera)) == NULL)
		return ;
	ft_matrix_free(camera->transform);
	camera->transform = transform;
}

t_matrix			*cam_transform(t_camera *camera)
{
	t_matrix *tmp;
	t_matrix *transform;

	if ((tmp = ft_matrix_new(4, 4)) == NULL ||
		(transform = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	if (ft_matrix_mul(camera->projection, camera->view, tmp) == FALSE ||
		ft_matrix_mul(
			camera->unit_scale, tmp, transform) == FALSE)
		return (NULL);
	ft_matrix_free(tmp);
	return (transform);
}

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
		(camera->color = ft_itorgb(MAP_COLOR)) == NULL ||
		(camera->view = ft_fps_cam(position, pitch, yaw)) == NULL ||
		(camera->projection = ft_perspective_matrix(camera->canvas)) == NULL ||
		(camera->unit_scale =
			ft_scale_matrix_xyz(SCALE, SCALE, SCALE)) == NULL ||
		(camera->transform = cam_transform(camera)) == NULL)
		return (NULL);
	camera->pitch = pitch;
	camera->yaw = yaw;
	camera->perspective = PERSPECTIVE;
	camera->position = position;
	return (camera);
}

t_scene				*new_scene(void *mlx, void *mlx_wdw, t_map *map)
{
	t_scene		*scene;
	t_camera	*camera;
	t_vector	*cam_pos;
	t_vector	*cam_up;
	double		arr[3];

	arr[0] = map->x_max;
	arr[1] = map->y_max;
	arr[2] = map->z_max;
	if ((cam_pos = ft_vector4_new(map->center->v[0], map->center->v[1],
						Z_POS_INIT + ft_max_double(arr, 3) + 5.15)) == NULL ||
		(cam_up = ft_vector4_new(0, 1, 0)) == NULL ||
		(camera = new_camera(cam_pos, cam_up, map)) == NULL ||
		(scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->camera = camera;
	scene->map = map;
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	scene->mouse_right_pressed = FALSE;
	scene->mouse_x = 0;
	scene->mouse_y = 0;
	return (scene);
}
