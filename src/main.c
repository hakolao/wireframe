/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 19:04:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Resets map rotation & scale to original values. May
** have some rounding diffrences.
*/

static int		reset_map(t_map *map)
{
	if (ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) == FALSE ||
		ft_matrix_mul_vector_lst(map->reset_scale, map->vertices,
			map->vertex_count) == FALSE)
		return (0);
	ft_matrix_free(map->rotation);
	ft_matrix_free(map->scale);
	ft_matrix_free(map->reset_rotation);
	ft_matrix_free(map->reset_scale);
	if ((map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL ||
		(map->reset_rotation =
			ft_matrix_inverse_4x4(map->rotation)) == NULL ||
		(map->scale = ft_matrix_id(4, 4)) == NULL ||
		(map->reset_scale =
			ft_matrix_inverse_4x4(map->scale)) == NULL)
		return (0);
	set_map_info(map);
	return (1);
}

/*
** Frees camera struct so camera can be reset
*/

static void		camera_free(t_camera *camera)
{
	ft_matrix_free(camera->projection);
	ft_matrix_free(camera->view);
	ft_matrix_free(camera->transform);
	ft_matrix_free(camera->unit_scale);
	ft_vector_free(camera->position);
	ft_vector_free(camera->init_position);
	ft_vector_free(camera->up);
	free(camera->canvas);
	free(camera);
}

/*
** Initializes the scene
*/

int				init(t_scene *scene)
{
	t_camera	*camera;

	if (reset_map(scene->map) == FALSE ||
		rotate_map(scene->map, 45, 0, 0) == FALSE)
		return (0);
	if ((camera = new_camera(scene->camera->init_position,
		scene->camera->up, scene->map)) == NULL)
		return (0);
	camera_free(scene->camera);
	scene->camera = camera;
	draw(scene);
	return (1);
}

/*
** Initializes fdf app creating new scene
*/

int				init_fdf(t_map *map)
{
	t_scene		*scene;
	void		*mlx;
	void		*mlx_wdw;

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
		"Wireframe - ohakola");
	if ((scene = new_scene(mlx, mlx_wdw, map)) == NULL ||
		init(scene) == 0)
		return (0);
	mlx_hook(mlx_wdw, 2, 0, handle_key_events, scene);
	mlx_hook(mlx_wdw, 4, 0, handle_mouse_button_press, scene);
	mlx_hook(mlx_wdw, 5, 0, handle_mouse_button_release, scene);
	mlx_hook(mlx_wdw, 6, 0, handle_mouse_move, scene);
	mlx_loop(mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_map		*map;

	map = NULL;
	if (argc > 1)
		if ((map = serialize(argv[1])) == NULL &&
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT)))
			return (0);
	return (init_fdf(map));
}
