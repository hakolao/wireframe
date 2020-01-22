/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 18:35:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int		reset_map(t_map *map)
{
	if (ft_matrix_mul_vector_lst(map->reset_rotation, map->vertices,
			map->vertex_count) == FALSE)
		return (0);
	ft_matrix_free(map->rotation);
	if ((map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL)
		return (0);
	return (1);
}

int				reset_fdf(t_scene *scene)
{
	if (reset_map(scene->map) == FALSE ||
		rotate_map(scene->map, 45, 0, 0) == FALSE)
		return (0);
	draw(scene);
	return (1);
}

int				init_fdf(t_map *map)
{
	t_scene		*scene;
	void		*mlx;
	void		*mlx_wdw;

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
		"Wireframe - ohakola");
	if ((scene = new_scene(mlx, mlx_wdw, map)) == NULL ||
		reset_fdf(scene) == 0)
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
	{
		if ((map = serialize(argv[1])) == NULL)
		{
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT));
			return (0);
		}
		log_map(map);
	}
	return (init_fdf(map));
}
