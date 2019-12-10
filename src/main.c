/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 17:53:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	print_vertex(t_list *vertex)
{
	ft_putstr("(x: ");
	ft_putnbr(((t_vertex*)(vertex->content))->x);
	ft_putstr(", y: ");
	ft_putnbr(((t_vertex*)(vertex->content))->y);
	ft_putstr(", z: ");
	ft_putnbr(((t_vertex*)(vertex->content))->z);
	ft_putstr(")\n");
}

void	print_map(t_map *map)
{
	t_list	*vertex;

	vertex = map->vertices;
	while (vertex)
	{
		print_vertex(vertex);
		vertex = vertex->next;
	}
	ft_putstr("\nMAP:\nvertex_count: ");
	ft_putnbr(map->vertex_count);
	ft_putstr(", x_max: ");
	ft_putnbr(map->x_max);
	ft_putstr(", y_max: ");
	ft_putnbr(map->y_max);
	ft_putstr(", z_max: ");
	ft_putnbr(map->z_max);
	ft_putstr("\n");
}

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