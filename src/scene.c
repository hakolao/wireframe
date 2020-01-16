/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/16 12:47:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_canvas		*new_canvas()
{
	t_canvas	*c;

	if ((c = (t_canvas*)malloc(sizeof(*c))) == NULL)
		return (NULL);
	c->width = WINDOW_WIDTH;
	c->height = WINDOW_HEIGHT;
	c->near = 0.1;
	c->far	= 50;
	c->angle = 70;
	return (c);
}

t_matrix		*cam_transform(t_camera *camera)
{
	t_matrix *transform;
	t_matrix *worldxview;

	if ((transform = ft_matrix_new(4, 4)) == NULL ||
		(worldxview = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	if (ft_matrix_mul(camera->world, camera->view, worldxview) == 0 ||
		ft_matrix_mul(worldxview, camera->projection, transform) == 0)
		return (NULL);
	ft_matrix_free(worldxview);
	return (transform);
}

static t_matrix *world_matrix(t_map *map)
{
	t_matrix	*world;
	
	if ((world = ft_scale_matrix(4, 4, map->scale)) == NULL)
		return (NULL);
	VALUE_AT(world, 2, 2) /= map->scale->v[2];
	VALUE_AT(world, 3, 3) = 1;
	return (world);
}

t_camera		*new_camera(t_vector *position, t_vector *up, t_map *map)
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
		(camera->world = world_matrix(map)) == NULL ||
		(camera->view = ft_fps_cam(position, pitch, yaw)) == NULL ||
		(camera->projection = ft_perspective_matrix(camera->canvas)) == NULL ||
		(camera->transform = cam_transform(camera)) == NULL)
		return (NULL);
	camera->pitch = pitch;
	camera->yaw = yaw;
	camera->perspective = PERSPECTIVE;
	camera->position = position;
	camera->target = map->center;
	camera->up = up;
	return (camera);
}

t_scene		*new_scene(void *mlx, void *mlx_wdw, t_map *map)
{
	t_scene		*scene;
	t_camera	*camera;
	t_vector	*cam_pos;
	t_vector	*cam_up;

	if ((cam_pos = ft_vector4_new(map->center->v[0],
									map->center->v[1],
									Z_POS_INIT - map->z_max - 5)) == NULL ||
		(cam_up = ft_vector4_new(0, 1, 0)) == NULL ||
		(camera = new_camera(cam_pos, cam_up, map)) == NULL ||
		(scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->camera = camera;
	scene->map = map;
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	return (scene);
}