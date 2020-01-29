/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/29 16:32:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Switch map
*/

int					switch_map(t_scene *scene)
{
	int		map_i;

	map_i = scene->map_index;
	map_i = map_i + 1 > scene->map_count - 1 ?
		0 : map_i + 1;
	init_scene(scene, map_i);
	return (0);
}

/*
** Camera distance
*/

static double		cam_distance(t_map *map)
{
	double		arr[3];

	arr[0] = map->x_max;
	arr[1] = map->y_max;
	arr[2] = map->z_max;
	return (ft_max_double(arr, 3));
}

/*
** Initializes the scene
*/

int					init_scene(t_scene *scene, int map_i)
{
	t_camera	*camera;
	t_vector	***xyz;
	t_vector	*cam_pos;
	t_vector	*cam_up;

	scene->map_index = map_i;
	if (reset_map(scene->maps[map_i]) == FALSE ||
		rotate_map(scene->maps[map_i], 45, 0, 0) == FALSE ||
		(cam_pos = ft_vector4_new(0, 0,
			cam_distance(scene->maps[map_i]) + 5.15)) == NULL ||
		(cam_up = ft_vector4_new(0, 1, 0)) == NULL ||
		(camera = new_camera(cam_pos, cam_up, scene->maps[map_i])) == NULL ||
		(xyz = axes(cam_distance(scene->maps[map_i]) * 6)) == NULL)
		return (0);
	if (scene->camera != NULL)
		camera_free(scene->camera);
	if (scene->axes != NULL)
		free_axes(scene->axes, scene->axis_len);
	scene->axis_len = cam_distance(scene->maps[map_i]) * 6;
	ft_vector_free(cam_pos);
	ft_vector_free(cam_up);
	scene->camera = camera;
	scene->axes = xyz;
	scene->redraw = TRUE;
	return (1);
}

/*
** Set render related params
*/

int					scene_render_params(t_scene *scene,
					void *mlx, void *mlx_wdw)
{
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	scene->pixel_bits = 32;
	scene->line_bytes = WINDOW_WIDTH * 4;
	scene->pixel_endian = TRUE;
	if ((scene->frame = mlx_new_image(mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT)) == NULL ||
		(scene->frame_buf =
		mlx_get_data_addr(scene->frame, &scene->pixel_bits,
			&scene->line_bytes, &scene->pixel_endian)) == NULL)
		return (FALSE);
	scene->redraw = FALSE;
	scene->col_r = 255;
	scene->col_g = 255;
	scene->col_b = 255;
	scene->col_a = 255;
	return (TRUE);
}

/*
** Creates a new scene containing all needed information. Set's
** camera's position based on map's size
*/

t_scene				*new_scene(void *mlx, void *mlx_wdw,
					t_map **maps)
{
	t_scene		*scene;

	if ((scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->maps = maps;
	scene->camera = NULL;
	scene->axes = NULL;
	if (scene_render_params(scene, mlx, mlx_wdw) == FALSE ||
		init_scene(scene, 0) == FALSE)
		return (NULL);
	scene->mouse_right_pressed = FALSE;
	scene->mouse_x = FALSE;
	scene->mouse_y = FALSE;
	scene->show_guide = FALSE;
	return (scene);
}
