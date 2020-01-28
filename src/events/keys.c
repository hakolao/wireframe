/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 14:18:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function containing key event checks for producing
** intended app behavior
*/

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
** Increment scene global colors
*/

static int		increment_scene_colors(t_scene *scene)
{
	scene->col_r = scene->col_r + 52 >= 255 ?
		0 + scene->col_r + 52 - 255 : scene->col_r + 52;
	scene->col_g = scene->col_g + 105 >= 255 ?
		0 + scene->col_g + 105 - 255 : scene->col_g + 105;
	scene->col_b = scene->col_b + 159 >= 255 ?
		0 + scene->col_b + 159 - 255 : scene->col_b + 159;
	scene->col_a = scene->col_a + 36 >= 255 ?
		0 + scene->col_a + 36 - 255 : scene->col_a + 36;
	return (0);
}

/*
** Key event handling
*/

int				handle_key_events(int key, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	if (key == KEY_G)
		scene->show_guide = !(scene->show_guide);
	if ((key == KEY_C && increment_scene_colors(scene)) ||
		(key == KEY_TAB && switch_map(scene)) ||
		(key == KEY_P && loop_perspective(scene->camera)) ||
		(key == KEY_R && init_scene(scene, scene->map_index)) ||
		(key == KEY_1 && zoom(scene->camera, 1)) ||
		(key == KEY_2 && zoom(scene->camera, -1)))
		;
	scene->redraw = TRUE;
	return (check_rest_of_events(key, scene));
}
