/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 22:06:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Initializes fdf app
*/

int				init_fdf(t_map **maps, int map_count)
{
	t_scene		*scene;
	void		*mlx;
	void		*mlx_wdw;

	if (((mlx = mlx_init()) == NULL ||
		(mlx_wdw = mlx_new_window(mlx, WIDTH, HEIGHT,
		"Wireframe - ohakola")) == NULL ||
		(scene = new_scene(mlx, mlx_wdw, maps)) == NULL) &&
			log_err("Failed to create scene.", strerror(ERRNO_IN)))
		return (0);
	scene->map_count = map_count;
	mlx_hook(mlx_wdw, 2, 0, handle_key_press, scene);
	mlx_hook(mlx_wdw, 3, 0, handle_key_release, scene);
	mlx_hook(mlx_wdw, 4, 0, handle_mouse_button_press, scene);
	mlx_hook(mlx_wdw, 5, 0, handle_mouse_button_release, scene);
	mlx_hook(mlx_wdw, 6, 0, handle_mouse_move, scene);
	mlx_hook(mlx_wdw, 17, 0, handle_exit_event, scene);
	mlx_loop_hook(mlx, handle_loop, scene);
	mlx_loop(mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_map		**maps;
	int			i;

	if (argc > 1)
	{
		if ((maps = (t_map**)malloc(sizeof(t_map*) * (argc - 1))) == NULL)
			return (0);
		i = 1;
		while (i < argc)
		{
			if ((maps[i - 1] = serialize_map(argv[i])) == NULL)
				return (0);
			i++;
		}
		init_fdf(maps, argc - 1);
	}
	return (0);
}
