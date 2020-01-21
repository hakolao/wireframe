/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/21 13:21:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int				handle_key_events(int key, void *param)
{
	t_scene	*scene;
	int 	ret;

	scene = (t_scene *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	ret = ((key == KEY_W && rotate_map(scene->map, 3, 0, 0)) ||
			(key == KEY_S && rotate_map(scene->map, -3, 0, 0)) ||
			(key == KEY_A && rotate_map(scene->map, 0, 3, 0)) ||
			(key == KEY_D && rotate_map(scene->map, 0, -3, 0)) ||
			(key == KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
			(key == KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
			(key == KEY_UP && move_camera_z(scene, 1)) ||
			(key == KEY_DOWN && move_camera_z(scene, -1)) ||
			(key == KEY_RIGHT && move_camera_x(scene, 1)) ||
			(key == KEY_LEFT && move_camera_x(scene, -1)) ||
			(key == KEY_NUM_4 && turn_camera(scene, 0, -2)) ||
			(key == KEY_NUM_6 && turn_camera(scene, 0, 2)) ||
			(key == KEY_NUM_8 && turn_camera(scene, 2, 0)) ||
			(key == KEY_NUM_2 && turn_camera(scene, -2, 0)) ||
			(key == KEY_P && loop_perspective(scene)) ||
			(key == KEY_R && reset_fdf(scene)) ||
			(key == KEY_1 && zoom(scene, 1)) ||
			(key == KEY_2 && zoom(scene, -1)));
	draw(scene);
	return (ret);
}

int				handle_mouse_button_press(int button, int x, int y, void *param)
{
	t_scene	*scene;
	int 	ret;

	scene = (t_scene *)param;
	ret = ((button == SCROLL_UP && scale_map_z(scene->map, 1.1)) ||
			(button == SCROLL_DOWN && scale_map_z(scene->map, 0.9)));
	if (button == MOUSE_BUTTON_RIGHT)
	{
		scene->mouse_right_pressed = TRUE;
		scene->mouse_x = x;
		scene->mouse_y = y;
	}
	draw(scene);
	return (ret);
}

int				handle_mouse_button_release(int button, int x, int y, void *param)
{
	t_scene	*scene;

	(void)x;
	(void)y;
	scene = (t_scene *)param;
	if (button == MOUSE_BUTTON_RIGHT)
		scene->mouse_right_pressed = FALSE;
	return (1);
}

int				handle_mouse_move(int x, int y, void *param)
{
	t_scene	*scene;
	int		x_diff;
	int		y_diff;

	scene = (t_scene *)param;
	if (scene->mouse_right_pressed == TRUE)
	{
		x_diff = x - scene->mouse_x;
		y_diff = y - scene->mouse_y;
		if (ft_abs(x_diff) > 5)
		{
			rotate_map(scene->map, 0, x_diff > 0 ? -2 : 2, 0);
			scene->mouse_x = x;
		}
		if (ft_abs(y_diff) > 5)
		{
			rotate_map(scene->map, y_diff > 0 ? -2 : 2, 0, 0);
			scene->mouse_y = y;
		}
		draw(scene);
	}
	return (1);
}

/*
** Handle events on Home computer... (different keycodes)
** int				handle_key_events_home(int key, void *param)
** {
** 	t_scene	*scene;
** 	int 	ret;
** 
** 	scene = (t_scene *)param;
** 	if (key == HOME_KEY_ESC)
** 	{
** 		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
** 		exit(0);
** 	}
** 	ret = ((key == HOME_KEY_W && rotate_map(scene->map, 3, 0, 0)) ||
** 			(key == HOME_KEY_S && rotate_map(scene->map, -3, 0, 0)) ||
** 			(key == HOME_KEY_A && rotate_map(scene->map, 0, 3, 0)) ||
** 			(key == HOME_KEY_D && rotate_map(scene->map, 0, -3, 0)) ||
** 			(key == HOME_KEY_Q && rotate_map(scene->map, 0, 0, -3)) ||
** 			(key == HOME_KEY_E && rotate_map(scene->map, 0, 0, 3)) ||
** 			(key == HOME_KEY_UP && move_camera_z(scene, 1)) ||
** 			(key == HOME_KEY_DOWN && move_camera_z(scene, -1)) ||
** 			(key == HOME_KEY_RIGHT && move_camera_x(scene, 1)) ||
** 			(key == HOME_KEY_LEFT && move_camera_x(scene, -1)) ||
** 			(key == HOME_KEY_J && turn_camera(scene, 0, -2)) ||
** 			(key == HOME_KEY_K && turn_camera(scene, 0, 2)) ||
** 			(key == HOME_KEY_I && turn_camera(scene, 2, 0)) ||
** 			(key == HOME_KEY_M && turn_camera(scene, -2, 0)) ||
** 			(key == HOME_KEY_P && loop_perspective(scene)) ||
** 			(key == HOME_KEY_1 && zoom(scene, 1)) ||
** 			(key == HOME_KEY_2 && zoom(scene, -1)) ||
** 			(key == HOME_PLUS && scale_map_z(scene->map, 1.1)) ||
** 			(key == HOME_MINUS && scale_map_z(scene->map, 0.9)));
** 	draw(scene);
** 	return (ret);
** }
*/