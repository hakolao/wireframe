/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 12:15:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Function containing key event checks for producing
** intended app behavior
*/

static int		check_key_events(int key, t_scene *scene)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	return ((key == KEY_UP && rotate_map(scene->map, 3, 0, 0)) ||
		(key == KEY_DOWN && rotate_map(scene->map, -3, 0, 0)) ||
		(key == KEY_LEFT && rotate_map(scene->map, 0, 3, 0)) ||
		(key == KEY_RIGHT && rotate_map(scene->map, 0, -3, 0)) ||
		(key == KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
		(key == KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
		(key == KEY_W && move_camera_forward(scene->camera, 1.5)) ||
		(key == KEY_S && move_camera_forward(scene->camera, -1.5)) ||
		(key == KEY_D && strafe_camera(scene->camera, 1.5)) ||
		(key == KEY_A && strafe_camera(scene->camera, -1.5)) ||
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
	ret = check_key_events(key, scene);
	draw(scene);
	return (ret);
}

/*
** Mouse button presses
*/

int				handle_mouse_button_press(int button, int x, int y, void *param)
{
	t_scene		*scene;
	int			ret;

	scene = (t_scene *)param;
	ret = ((button == SCROLL_UP && scale_map(scene->map, 1, 1, 1.1)) ||
			(button == SCROLL_DOWN && scale_map(scene->map, 1, 1, 0.9)));
	if (button == MOUSE_BUTTON_RIGHT)
	{
		scene->mouse_right_pressed = TRUE;
		scene->mouse_x = x;
		scene->mouse_y = y;
	}
	if (button == MOUSE_BUTTON_LEFT)
	{
		scene->mouse_left_pressed = TRUE;
		scene->mouse_x = x;
		scene->mouse_y = y;
	}
	draw(scene);
	return (ret);
}

/*
** Mouse button releases
*/

int				handle_mouse_button_release(int button, int x, int y,
				void *param)
{
	t_scene	*scene;

	(void)x;
	(void)y;
	scene = (t_scene *)param;
	if (button == MOUSE_BUTTON_RIGHT)
		scene->mouse_right_pressed = FALSE;
	if (button == MOUSE_BUTTON_LEFT)
		scene->mouse_left_pressed = FALSE;
	return (1);
}

/*
** Mouse movement
*/

int				handle_mouse_move(int x, int y, void *param)
{
	t_scene	*scene;
	int		x_diff;
	int		y_diff;
	int		diff_lim;

	scene = (t_scene *)param;
	x_diff = x - scene->mouse_x;
	y_diff = y - scene->mouse_y;
	diff_lim = 5;
	if (scene->mouse_right_pressed == TRUE && ft_abs(x_diff) > diff_lim &&
		rotate_map(scene->map, 0, x_diff > 0 ? 2 : -2, 0) && draw(scene))
		scene->mouse_x = x;
	else if (scene->mouse_right_pressed == TRUE && ft_abs(y_diff) > diff_lim &&
		rotate_map(scene->map, y_diff > 0 ? -2 : 2, 0, 0) && draw(scene))
		scene->mouse_y = y;
	else if (scene->mouse_left_pressed == TRUE && ft_abs(x_diff) > diff_lim &&
		turn_camera(scene->camera, 0, x_diff > 0 ? -2 : 2) && draw(scene))
		scene->mouse_x = x;
	else if (scene->mouse_left_pressed == TRUE && ft_abs(y_diff) > diff_lim &&
		turn_camera(scene->camera, y_diff > 0 ? 2 : -2, 0) && draw(scene))
		scene->mouse_y = y;
	return (1);
}
