/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/08 15:46:02 by ohakola          ###   ########.fr       */
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
	c->far	= 100;
	c->angle = 70;
	return (c);
}

t_matrix		*cam_transform(t_map *map, t_matrix *view,
					t_matrix *projection)
{
	t_matrix *world;
	t_matrix *transform;
	t_matrix *projxview;

	if ((world = ft_scale_matrix(4, 4, map->scale)) == NULL ||
		(transform = ft_matrix_new(4, 4)) == NULL ||
		(projxview = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	if (ft_matrix_mul(projection, view, projxview) == 0 ||
		ft_matrix_mul(projxview, world, transform) == 0)
		return (NULL);
	ft_matrix_free(world);
	ft_matrix_free(projxview);
	return (transform);
}

t_camera		*new_camera(t_vector *position, t_vector *up, t_map *map)
{
	t_camera	*camera;

	if (position == NULL || map->center == NULL || up == NULL ||
		(camera = (t_camera*)malloc(sizeof(*camera))) == NULL ||
		(camera->canvas = new_canvas()) == NULL ||
		(camera->color = ft_itorgb(MAP_COLOR)) == NULL ||
		(camera->view = ft_view_matrix(position, map->center, up)) == NULL ||
		(camera->projection = ft_perspective_matrix(camera->canvas)) == NULL ||
		(camera->transform =
			cam_transform(map, camera->view, camera->projection)) == NULL)
		return (NULL);
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
									map->center->v[1], Z_POS_INIT)) == NULL ||
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