/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:21:55 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 13:17:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		log_vertex(t_list *vertex)
{
	ft_putstr("(");
	ft_putnbr(((t_vector*)(vertex->content))->v[0]);
	ft_putstr(", ");
	ft_putnbr(((t_vector*)(vertex->content))->v[1]);
	ft_putstr(", ");
	ft_putnbr(((t_vector*)(vertex->content))->v[2]);
	ft_putstr(")\n");
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
}

void			log_error(char *str, char *strerror)
{
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
}