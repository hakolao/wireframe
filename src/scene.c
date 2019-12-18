/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 15:42:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_canvas		*new_canvas(int width, int height)
{
	t_canvas	*c;

	if ((c = (t_canvas*)malloc(sizeof(*c))) == NULL)
		return (NULL);
	c->width = width;
	c->height = height;
	return (c);
}

t_matrix		*ft_view_matrix(t_vector *position, t_vector *target, t_vector *up)
{
	t_vector	*forward;
	t_vector	*sideways;
	t_vector	*v;
	t_matrix	*view;
	double		vals[16];

	if ((forward = ft_vector_normalize(ft_vector_sub(position, target))) == NULL)
		return (NULL);
	if ((sideways = ft_vector_normalize(ft_vector_cross(forward, up))) == NULL)
		return (NULL);
	if ((v = ft_vector_cross(sideways, forward)) == NULL)
		return (NULL);
	if ((view = ft_matrix_new(4, 4)) == NULL)
		return (NULL);
	vals[0] = sideways->v[0];
	vals[1] = sideways->v[1];
	vals[2] = sideways->v[2];
	vals[3] = 0;
	vals[4] = v->v[0];
	vals[5] = v->v[1];
	vals[6] = v->v[2];
	vals[7] = 0;
	vals[8] = forward->v[0];
	vals[9] = forward->v[1];
	vals[10] = forward->v[2];
	vals[11] = 0;
	vals[12] = position->v[0];
	vals[13] = position->v[1];
	vals[14] = position->v[2];
	vals[15] = 0;
	ft_matrix_set_vals(view, vals, 16);
	return (view);
}

t_camera		*new_camera(t_vector *position, t_vector *target, t_vector *up)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_rgb		*color;
	t_matrix	*view;

	if ((camera = (t_camera*)malloc(sizeof(*camera))) == NULL || position == NULL)
		return (NULL);
	if ((canvas = new_canvas(2.0, 2.0)) == NULL)
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