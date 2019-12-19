/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 19:49:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_wdw;
	t_map		*map;
	t_scene		*scene;

	map = NULL;
	scene = NULL;
	if (argc > 1)
	{
		if ((map = serialize(argv[1])) == NULL)
		{
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT));
			return (0);
		}
		log_map(map);
	}

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe - ohakola");
	if ((scene = new_scene(mlx, mlx_wdw, map)) == NULL)
		return (0);
	draw(scene);
	mlx_key_hook(mlx_wdw, handle_key_events, scene);
	mlx_do_key_autorepeaton(mlx);
	mlx_loop(mlx);
	return (0);
}