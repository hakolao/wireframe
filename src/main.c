/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 18:23:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initializes fdf app
*/

int				init_fdf(t_map *map)
{
	t_scene		*scene;
	void		*frame;
	void		*mlx;
	void		*mlx_wdw;

	if ((mlx = mlx_init()) == NULL ||
		(mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
		"Wireframe - ohakola")) == NULL ||
		(frame = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT))
			== NULL ||
		(scene = new_scene(mlx, mlx_wdw, frame, map)) == NULL ||
		init(scene) == 0)
		return (0);
	mlx_hook(mlx_wdw, 2, 0, handle_key_events, scene);
	mlx_hook(mlx_wdw, 4, 0, handle_mouse_button_press, scene);
	mlx_hook(mlx_wdw, 5, 0, handle_mouse_button_release, scene);
	mlx_hook(mlx_wdw, 6, 0, handle_mouse_move, scene);
	mlx_loop_hook(mlx, handle_loop, scene);
	mlx_loop(mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_map		*map;

	map = NULL;
	if (argc > 1)
		if ((map = serialize_map(argv[1])) == NULL &&
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT)))
			return (0);
	return (init_fdf(map));
}
