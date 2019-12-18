/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 17:08:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_wdw;
	t_camera	*camera;
	t_map		*map;
	t_scene		*scene;

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe");

	map = NULL;
	camera = NULL;
	if (argc > 1)
	{
		if ((map = serialize(argv[1])) == NULL)
		{
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT));
			return (0);
		}
		log_map(map);
	}
	if ((camera = new_camera(ft_vector4_new(0.0, 0.0, -10.0),
					ft_vector4_new(0, 0, 0),
					ft_vector4_new(0, 1, 0))) == NULL)
		return (0);
	if ((scene = new_scene(map, camera)) == NULL)
		return (0);
	mlx_key_hook(mlx_wdw, handle_key_events, scene);
	draw(mlx, mlx_wdw, scene);
	mlx_loop(mlx);
	return (0);
}