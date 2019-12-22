/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:21:55 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 18:07:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void		log_vertex(t_vector *vertex)
{
	ft_putstr("Vertex: ");
	ft_putvector(vertex);
}

int				log_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->vertex_count)
	{
		log_vertex(map->vertices[i]);
		i++;
	}
	ft_putstr("\nMAP:\nvertex_count: ");
	ft_putnbr(map->vertex_count);
	ft_putstr(", x_min: ");
	ft_putnbr(map->x_min);
	ft_putstr(", y_min: ");
	ft_putnbr(map->y_min);
	ft_putstr(", z_min: ");
	ft_putnbr(map->z_min);
	ft_putstr("\n");
	ft_putstr(", x_max: ");
	ft_putnbr(map->x_max);
	ft_putstr(", y_max: ");
	ft_putnbr(map->y_max);
	ft_putstr(", z_max: ");
	ft_putnbr(map->z_max);
	ft_putstr("\n");
	ft_putstr("Center:\n");
	ft_putvector(map->center);
	return (1);
}

int				log_error(char *str, char *strerror)
{
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

int				log_perror(char *str)
{
	perror(str);
	return (1);
}