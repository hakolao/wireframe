/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/20 17:45:40 by ohakola          ###   ########.fr       */
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

t_camera			*new_camera(t_vector *position, t_vector *target, t_vector *up)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_rgb		*color;
	t_matrix	*view;
	t_matrix	*projection;

	if ((camera = (t_camera*)malloc(sizeof(*camera))) == NULL || position == NULL)
		return (NULL);
	if ((canvas = new_canvas()) == NULL)
		return (NULL);
	if ((color = ft_itorgb(MAP_COLOR)) == NULL)
		return (NULL);
	if ((view = ft_view_matrix(position, target, up)) == NULL)
		return (NULL);
	if ((projection = ft_perspective_matrix(canvas)) == NULL)
		return (NULL);
	camera->position = position;
	camera->canvas = canvas;
	camera->color = color;
	camera->view = view;
	camera->projection = projection;
	camera->transform = NULL;
	camera->target = target;
	camera->up = up;
	return (camera);
}

t_scene		*new_scene(void *mlx, void *mlx_wdw, t_map *map)
{
	t_scene		*scene;
	t_camera	*camera;

	if ((camera = new_camera(
					ft_vector4_new(map->center->v[0], map->center->v[1], Z_POS_INIT),
					map->center,
					ft_vector4_new(0, 1, 0))) == NULL)
		return (NULL);
	if ((scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->camera = camera;
	scene->map = map;
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	return (scene);
}