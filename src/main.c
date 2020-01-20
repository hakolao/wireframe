/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/20 17:32:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	reset_fdf(t_scene *scene)
{
	if (reset_map(scene->map) == FALSE ||
		rotate_map(scene->map, 45, 0, 0) == FALSE)
		return (0);
	draw(scene);
	return (0);
}

int	init_fdf(t_map *map)
{
	t_scene		*scene;
	void		*mlx;
	void		*mlx_wdw;
	
	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe - ohakola");
	if ((scene = new_scene(mlx, mlx_wdw, map)) == NULL)
		return (0);
	reset_fdf(scene);
	// mlx_key_hook(mlx_wdw, handle_key_events_home, scene);
	mlx_hook(mlx_wdw, 2, 0, handle_key_events, scene);
	mlx_hook(mlx_wdw, 4, 0, handle_mouse_button_press, scene);
	mlx_hook(mlx_wdw, 5, 0, handle_mouse_button_release, scene);
	mlx_hook(mlx_wdw, 6, 0, handle_mouse_move, scene);
	// mlx_loop_hook(mlx_wdw, handle_map_rotation, scene);
	mlx_loop(mlx);
	return (0);
}

int		main(int argc, char **argv)
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
