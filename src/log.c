/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:21:55 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/19 21:15:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		log_vertex(t_list *vertex)
{
	ft_putstr("Vertex: ");
	ft_putvector((t_vector*)(vertex->content));
}

void			log_map(t_map *map)
{
	t_list	*vertex;

	vertex = map->vertices;
	while (vertex)
	{
		log_vertex(vertex);
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
	ft_putstr("Center:\n");
	ft_putvector(map->center);
}

void			log_error(char *str, char *strerror)
{
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
}