/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:48 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:06:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				handle_mouse_button_press(int button, int x, int y, void *param)
{
	t_scene		*scene;
	int			ret;

	scene = (t_scene *)param;
	ret = ((button == SCROLL_UP &&
				scale_map(scene->maps[scene->map_index], 1, 1, 1.1)) ||
			(button == SCROLL_DOWN &&
				scale_map(scene->maps[scene->map_index], 1, 1, 0.9)));
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
	scene->redraw = TRUE;
	return (ret);
}

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
	scene->redraw = TRUE;
	return (1);
}

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
		rotate_map(scene->maps[scene->map_index], 0, x_diff > 0 ? 2 : -2, 0))
		scene->mouse_x = x;
	else if (scene->mouse_right_pressed == TRUE && ft_abs(y_diff) > diff_lim &&
		rotate_map(scene->maps[scene->map_index], y_diff > 0 ? -2 : 2, 0, 0))
		scene->mouse_y = y;
	else if (scene->mouse_left_pressed == TRUE && ft_abs(x_diff) > diff_lim &&
		turn_camera(scene->camera, 0, x_diff > 0 ? -3 : 3))
		scene->mouse_x = x;
	else if (scene->mouse_left_pressed == TRUE && ft_abs(y_diff) > diff_lim &&
		turn_camera(scene->camera, y_diff > 0 ? 3 : -3, 0))
		scene->mouse_y = y;
	if (scene->mouse_left_pressed || scene->mouse_right_pressed)
		scene->redraw = TRUE;
	return (1);
}
