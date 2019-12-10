/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 15:33:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*mlx_wdw;

	(void)argc;
	(void)argv;
	mlx_ptr = mlx_init();
	mlx_wdw = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe");
	mlx_loop(mlx_ptr);
	return (0);
}