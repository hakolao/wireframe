/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 20:41:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	zoom_camera(t_scene *scene, double dir)
{
	t_matrix	*projection;
	double		new_angle;
	double		old_angle;

	old_angle = scene->camera->canvas->angle;
	new_angle = scene->camera->canvas->angle + dir * ZOOM_SPEED;
	new_angle = new_angle > 0 && new_angle < 180 ? new_angle : scene->camera->canvas->angle;
	scene->camera->canvas->angle = new_angle;
	if ((projection = ft_perspective_matrix(scene->camera->canvas)) == NULL)
	{
		scene->camera->canvas->angle = old_angle;
		return ;
	}
	ft_matrix_free(scene->camera->projection);
	scene->camera->projection = projection;
	draw(scene);
}

int		handle_key_events(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	// ft_putnbr(key);
	if (key == KEY_W)
		zoom_camera(scene, -1);
	if (key == KEY_S)
		zoom_camera(scene, 1);
	return (0);
}