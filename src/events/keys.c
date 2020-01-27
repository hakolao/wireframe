/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 18:24:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function containing key event checks for producing
** intended app behavior
*/

static int		check_key_events(int key, t_scene *scene)
{
	return ((key == KEY_UP && rotate_map(scene->map, 3, 0, 0)) ||
		(key == KEY_DOWN && rotate_map(scene->map, -3, 0, 0)) ||
		(key == KEY_LEFT && rotate_map(scene->map, 0, 3, 0)) ||
		(key == KEY_RIGHT && rotate_map(scene->map, 0, -3, 0)) ||
		(key == KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
		(key == KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
		(key == KEY_W && move_camera_forward(scene->camera, 0.2)) ||
		(key == KEY_S && move_camera_forward(scene->camera, -0.2)) ||
		(key == KEY_D && strafe_camera(scene->camera, 0.2)) ||
		(key == KEY_A && strafe_camera(scene->camera, -0.2)) ||
		(key == KEY_NUM_4 && turn_camera(scene->camera, 0, 2)) ||
		(key == KEY_NUM_6 && turn_camera(scene->camera, 0, -2)) ||
		(key == KEY_NUM_8 && turn_camera(scene->camera, -2, 0)) ||
		(key == KEY_NUM_2 && turn_camera(scene->camera, 2, 0)) ||
		(key == KEY_P && loop_perspective(scene->camera)) ||
		(key == KEY_R && init(scene)) ||
		(key == KEY_1 && zoom(scene->camera, 1)) ||
		(key == KEY_2 && zoom(scene->camera, -1)) ||
		(key == KEY_NUM_PLUS && scale_map(scene->map, 1.1, 1.1, 1.1)) ||
		(key == KEY_NUM_MINUS && scale_map(scene->map, 0.9, 0.9, 0.9)));
}

/*
** Key event handling
*/

int				handle_key_events(int key, void *param)
{
	t_scene		*scene;
	int			ret;

	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	if (key == KEY_G)
		scene->show_guide = !(scene->show_guide);
	ret = check_key_events(key, scene);
	scene->redraw = TRUE;
	return (ret);
}
