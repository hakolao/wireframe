/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 12:55:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int		handle_keys(int key, void *param)
{
	t_map	*map;

	map = (t_map*)param;
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_wdw;
	t_map	*map;

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe");

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
	
	mlx_key_hook(mlx_wdw, handle_keys, map);
	mlx_loop(mlx);
	return (0);
}