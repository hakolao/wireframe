/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 01:03:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Sets map line related values when iterating line.
*/

static void			set_line_map_info(t_map *map, int x, int z)
{
	map->z_max = map->z_max >= z ? map->z_max : z;
	map->z_min = map->z_min <= z ? map->z_min : z;
	map->x_max = map->x_max >= x ? map->x_max : x;
	(map->vertex_count)++;
}

/*
** Reads one line of map data, validates it and sets
** xyz values as vertices to map. Reallocates if needed
*/

static int			read_map_line(char *line, int y, t_map *map)
{
	int			x;
	int			z;

	x = 0;
	while (*line)
	{
		if (!(*line == ' ' || *line == '-' || ft_isdigit(*line)) &&
			log_err(ERR_READ, strerror(ERRNO_IN)))
			return (FALSE);
		if (ft_isdigit(*line) || *line == '-')
		{
			z = read_z_from_digit(&line);
			if ((map->vertex_count >= map->size &&
				!(map->vertices = reallocate_map_vertices(map))) ||
				!(map->vertices[map->vertex_count] = ft_vector4_new(x, y, z)))
				return (FALSE);
			set_line_map_info(map, x, z);
			x++;
		}
		else
			line++;
	}
	if ((x == 0 && log_err(ERR_ZERO, strerror(ERRNO_IN))) ||
		(map->vertex_count % x != 0 && log_err(ERR_ROWS, strerror(ERRNO_IN))))
		return (FALSE);
	return (TRUE);
}

/*
** Reads map data with get_next_line and transforms it into a
** linked list. This linked list is then transformed to an
** array of vectors. y information is read here.
*/

static t_map		*file_to_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		y;

	y = 0;
	if (!init_vals_before_read(map))
		return (NULL);
	while ((ret = get_next_line(fd, &line)) == TRUE)
	{
		if (!read_map_line(line, y++, map))
			return (NULL);
		ft_strdel(&line);
	}
	if (ret == FALSE)
		map->y_max = y - 1;
	if ((((map->x = map->x_max) == 0 ||
			(map->y = map->y_max) == 0) && log_err(ERR_MAP, strerror(5))) ||
		(ret == -1 && log_perr("")))
		return (NULL);
	ft_strdel(&line);
	if (!shift_map_vertices(map) && log_err(ERR_CENTER, strerror(ERRNO_IN)))
		return (NULL);
	return (map);
}

/*
** Serializes read data into map struct
*/

t_map				*serialize_map(char *filename)
{
	t_map		*map;
	int			fd;

	if (((map = (t_map*)malloc(sizeof(*map))) == NULL ||
		((fd = open(filename, O_RDONLY)) == -1 && log_perr("")) ||
		(map = file_to_map(fd, map)) == NULL ||
		(map->center = ft_vector4_new(0, 0, 0)) == NULL ||
		(map->rotation = ft_matrix_new(4, 4)) == NULL ||
		!ft_rotation_matrix(0, 0, 0, map->rotation) ||
		(map->reset_rotation = ft_matrix_new(4, 4)) == NULL ||
		!ft_matrix_inverse_4x4(map->rotation, map->reset_rotation) ||
		(map->scale = ft_matrix_id(4, 4)) == NULL ||
		(map->reset_scale = ft_matrix_id(4, 4)) == NULL ||
		!ft_matrix_inverse_4x4(map->scale, map->reset_scale)) &&
		log_err(ft_strjoin("Error reading map: ", filename),
			strerror(ERRNO_IN)))
		return (NULL);
	map->col_r = 255;
	map->col_g = 255;
	map->col_b = 255;
	map->col_a = 255;
	map->name = filename;
	if (close(fd) == -1 && log_perr(""))
		return (NULL);
	return (map);
}
