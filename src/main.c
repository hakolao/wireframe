/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 18:01:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	main(int argc, char **argv)
{
	// void	*mlx_ptr;
	// void	*mlx_wdw;
	t_map	*map;

	// mlx_ptr = mlx_init();
	// mlx_wdw = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe");

	map = NULL;
	if (argc > 1)
	{
		if ((map = serialize(argv[1])) == NULL)
			return (0);
		print_map(map);
	}

	// mlx_loop(mlx_ptr);
	return (0);
}