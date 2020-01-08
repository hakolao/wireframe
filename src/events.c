/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:56:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/08 14:45:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		re_draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw(scene);
}

static void		re_project(t_scene *scene)
{
	t_matrix	*transform;
	t_matrix	*projection;

	if ((projection = ft_perspective_matrix(scene->camera->canvas)) == NULL ||
		(transform =
			cam_transform(scene->map, scene->camera->view, projection)) == NULL)
		return ;
	ft_matrix_free(scene->camera->transform);
	ft_matrix_free(scene->camera->projection);
	scene->camera->transform = transform;
	scene->camera->projection = projection;
}

static void		zoom(t_scene *scene, int dir)
{
	scene->camera->canvas->angle += dir;
	if (scene->camera->canvas->angle <= 0)
		scene->camera->canvas->angle = 70;
	if (scene->camera->canvas->angle >= 180)
		scene->camera->canvas->angle = 70;
	re_project(scene);
	re_draw(scene);
}

int				handle_key_events(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->mlx_wdw);
		exit(0);
	}
	if (key == KEY_W)
		zoom(scene, -1);
	if (key == KEY_S)
		zoom(scene, 1);
	return (0);
}