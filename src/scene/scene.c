/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 14:36:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initializes the scene
*/

int					init(t_scene *scene)
{
	t_camera	*camera;

	if (reset_map(scene->map) == FALSE ||
		rotate_map(scene->map, 45, 0, 0) == FALSE)
		return (0);
	if ((camera = new_camera(scene->camera->init_position,
		scene->camera->up, scene->map)) == NULL)
		return (0);
	camera_free(scene->camera);
	scene->camera = camera;
	draw(scene);
	return (1);
}

/*
** Creates a new scene containing all needed information. Set's
** camera's position based on map's size
*/

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
	ft_vector_free(cam_pos);
	ft_vector_free(cam_up);
	scene->camera = camera;
	scene->map = map;
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	scene->mouse_right_pressed = FALSE;
	scene->mouse_x = 0;
	scene->mouse_y = 0;
	scene->show_guide = 0;
	return (scene);
}
