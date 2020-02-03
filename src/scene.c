/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:13:53 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:14:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					switch_map(t_scene *scene, int dir)
{
	int		map_i;

	map_i = scene->map_index;
	map_i += dir;
	if (map_i > scene->map_count - 1)
		map_i = 0;
	if (map_i < 0)
		map_i = scene->map_count - 1;
	init_scene(scene, map_i);
	return (0);
}

static double		cam_distance(t_map *map)
{
	double		arr[3];

	arr[0] = map->x_max;
	arr[1] = map->y_max;
	arr[2] = map->z_max;
	return (ft_max_double(arr, 3));
}

int					init_scene(t_scene *scene, int map_i)
{
	t_camera	*camera;
	t_vector	*cam_pos;
	t_vector	*cam_up;
	t_map		*map;

	scene->map_index = map_i;
	map = scene->maps[map_i];
	if (!reset_map(map) || !rotate_map(map, 45, 0, 0) ||
		!scale_map(map, 1, 1, (map->y_max - map->y_min) /
			(8 * (map->z_max - map->z_min + 0.1))) ||
		!(cam_pos = ft_vector4_new(0, 0, cam_distance(map) + 5.15)) ||
		!(cam_up = ft_vector4_new(0, 1, 0)) ||
		!(camera = new_camera(cam_pos, cam_up, map)))
		return (0);
	if (scene->camera != NULL)
		camera_free(scene->camera);
	ft_vector_free(cam_pos);
	ft_vector_free(cam_up);
	scene->camera = camera;
	scene->redraw = TRUE;
	return (1);
}

int					scene_render_params(t_scene *scene,
					void *mlx, void *mlx_wdw)
{
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	scene->pixel_bits = 32;
	scene->line_bytes = WIDTH * 4;
	scene->pixel_endian = TRUE;
	if (!(scene->frame = mlx_new_image(mlx, WIDTH, HEIGHT)) ||
		!(scene->frame_buf =
			mlx_get_data_addr(scene->frame, &scene->pixel_bits,
			&scene->line_bytes, &scene->pixel_endian)))
		return (FALSE);
	scene->redraw = FALSE;
	scene->col_r = 0;
	scene->col_g = 0;
	scene->col_b = 0;
	scene->col_a = 0;
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
	if (scene_render_params(scene, mlx, mlx_wdw) == FALSE ||
		init_scene(scene, 0) == FALSE)
		return (NULL);
	scene->mouse_right_pressed = FALSE;
	scene->mouse_left_pressed = FALSE;
	scene->shift_pressed = FALSE;
	scene->mouse_x = FALSE;
	scene->mouse_y = FALSE;
	scene->show_guide = FALSE;
	scene->show_coords = FALSE;
	return (scene);
}
