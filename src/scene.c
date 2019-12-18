/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 16:56:12 by ohakola          ###   ########.fr       */
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
	c->near = 1;
	c->far	= 400;
	c->angle = M_PI / 2;
	return (c);
}

t_camera		*new_camera(t_vector *position, t_vector *target, t_vector *up)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_rgb		*color;
	t_matrix	*view;

	if ((camera = (t_camera*)malloc(sizeof(*camera))) == NULL || position == NULL)
		return (NULL);
	if ((canvas = new_canvas()) == NULL)
		return (NULL);
	if ((color = ft_itorgb(MAP_COLOR)) == NULL)
		return (NULL);
	if ((view = ft_view_matrix(position, target, up)) == NULL)
		return (NULL);
	camera->position = position;
	camera->canvas = canvas;
	camera->color = color;
	camera->zoom = ZOOM;
	camera->view_matrix = view;
	return (camera);
}

t_scene		*new_scene(t_map *map, t_camera *camera)
{
	t_scene	*scene;

	if ((scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->camera = camera;
	scene->map = map;
	return (scene);
}