/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:26:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:12:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector		**reallocate_map_vertices(t_map *map)
{
	t_vector	**tmp;
	size_t		i;

	if (!(tmp = malloc(sizeof(*(map->vertices)) * map->size * 2)))
		return (NULL);
	i = 0;
	while (i < map->size)
	{
		tmp[i] = map->vertices[i];
		i++;
	}
	free(map->vertices);
	map->vertices = tmp;
	map->size *= 2;
	return (map->vertices);
}

/*
** Reads z from digit line using ft_atoi.
*/

int				read_z_from_digit(char **line)
{
	int	z;

	z = ft_atoi(*line);
	while (*line && **line == '-')
		(*line)++;
	while (**line && ft_isdigit(**line))
		(*line)++;
	while (**line && **line == ' ')
		(*line)++;
	return (z);
}

/*
** Find z center of mass
*/

double			z_shift(t_map *map)
{
	double		sum;
	size_t		i;

	sum = 0;
	i = 0;
	while (i < map->vertex_count)
		sum += map->vertices[i++]->v[2];
	return (sum / (double)i);
}

/*
**	Initialize necessary values on map before read
*/

int				init_vals_before_read(t_map *map)
{
	map->vertex_count = 0;
	map->x_min = 0;
	map->x_max = 0;
	map->y_min = 0;
	map->y_max = 0;
	map->z_max = 0;
	map->z_min = 0;
	map->size = 1024;
	if (!(map->vertices = malloc(sizeof(*(map->vertices)) * map->size)))
		return (FALSE);
	return (TRUE);
}

/*
** Shifts map's pivot to it's center in 0, 0, 0.
*/

int				shift_map_vertices(t_map *map)
{
	t_vector	shift;
	size_t		i;

	shift = (t_vector){.v =
		(double[]){-map->x_max / 2, -map->y_max / 2, -z_shift(map), 1},
		.size = 4};
	i = 0;
	while (i < map->vertex_count)
	{
		if (!ft_vector_add(map->vertices[i], &shift, map->vertices[i]))
			return (0);
		map->vertices[i++]->v[3] = 1;
	}
	set_map_info(map);
	return (1);
}
