/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/17 17:44:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	init_fdf(t_map *map)
{
	t_scene		*scene;
	void		*mlx;
	void		*mlx_wdw;
	
	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe - ohakola");
	if ((scene = new_scene(mlx, mlx_wdw, map)) == NULL)
		return (0);
	// rotate_around_x(scene, 45);
	draw(scene);
	mlx_hook(mlx_wdw, 2, 0, handle_key_events, scene);
	mlx_hook(mlx_wdw, 4, 0, handle_mouse_button_events, scene);
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