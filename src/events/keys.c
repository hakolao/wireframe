/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:08:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		check_rest_of_events(int key, t_scene *scene)
{
	return ((key == KEY_UP &&
			rotate_map(scene->maps[scene->map_index], 3, 0, 0)) ||
		(key == KEY_DOWN &&
			rotate_map(scene->maps[scene->map_index], -3, 0, 0)) ||
		(key == KEY_LEFT &&
			rotate_map(scene->maps[scene->map_index], 0, 3, 0)) ||
		(key == KEY_RIGHT &&
			rotate_map(scene->maps[scene->map_index], 0, -3, 0)) ||
		(key == KEY_Q &&
			rotate_map(scene->maps[scene->map_index], 0, 0, -3)) ||
		(key == KEY_E &&
			rotate_map(scene->maps[scene->map_index], 0, 0, 3)) ||
		(key == KEY_W && move_camera_forward(scene->camera, 0.2)) ||
		(key == KEY_S && move_camera_forward(scene->camera, -0.2)) ||
		(key == KEY_D && strafe_camera(scene->camera, 0.2)) ||
		(key == KEY_A && strafe_camera(scene->camera, -0.2)) ||
		(key == KEY_NUM_4 && turn_camera(scene->camera, 0, 2)) ||
		(key == KEY_NUM_6 && turn_camera(scene->camera, 0, -2)) ||
		(key == KEY_NUM_8 && turn_camera(scene->camera, -2, 0)) ||
		(key == KEY_NUM_2 && turn_camera(scene->camera, 2, 0)) ||
		(key == KEY_NUM_PLUS &&
			scale_map(scene->maps[scene->map_index], 1.1, 1.1, 1.1)) ||
		(key == KEY_NUM_MINUS &&
			scale_map(scene->maps[scene->map_index], 0.9, 0.9, 0.9)));
}

/*
** Increment scene global colors (rand() is a forbidden function
** according to assignment, but it's allowed in bonus features)
*/

static int		change_scene_colors(t_scene *scene)
{
	t_map *map;

	map = scene->maps[scene->map_index];
	scene->col_r = rand() % 255;
	scene->col_g = rand() % 255;
	scene->col_b = rand() % 255;
	scene->col_a = rand() % 255;
	return (0);
}

/*
** Increment map global colors (rand() is a forbidden function
** according to assignment, but it's allowed in bonus features)
*/

static int		change_map_colors(t_scene *scene)
{
	t_map *map;

	map = scene->maps[scene->map_index];
	map->col_r = rand() % 255;
	map->col_g = rand() % 255;
	map->col_b = rand() % 255;
	return (0);
}

int				handle_key_press(int key, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	scene->redraw = TRUE;
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_SHIFT)
		scene->shift_pressed = TRUE;
	if (key == KEY_G)
		scene->show_guide = !(scene->show_guide);
	if (key == KEY_O)
		scene->show_coords = !(scene->show_coords);
	return ((key == KEY_B && change_scene_colors(scene)) ||
		(key == KEY_C && change_map_colors(scene)) ||
		((key == KEY_TAB && !scene->shift_pressed) &&
			scene->map_count > 1 && switch_map(scene, 1)) ||
		((key == KEY_TAB && scene->shift_pressed) &&
			scene->map_count > 1 && switch_map(scene, -1)) ||
		(key == KEY_P && loop_perspective(scene->camera)) ||
		(key == KEY_R && init_scene(scene, scene->map_index)) ||
		(key == KEY_1 && zoom(scene->camera, 1)) ||
		(key == KEY_2 && zoom(scene->camera, -1)) ||
		check_rest_of_events(key, scene));
}

int				handle_key_release(int key, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (key == KEY_SHIFT)
		scene->shift_pressed = FALSE;
	return (0);
}
