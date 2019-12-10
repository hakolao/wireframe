/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:00:16 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 18:01:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		print_vertex(t_list *vertex)
{
	ft_putstr("(x: ");
	ft_putnbr(((t_vertex*)(vertex->content))->x);
	ft_putstr(", y: ");
	ft_putnbr(((t_vertex*)(vertex->content))->y);
	ft_putstr(", z: ");
	ft_putnbr(((t_vertex*)(vertex->content))->z);
	ft_putstr(")\n");
}

void			print_map(t_map *map)
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