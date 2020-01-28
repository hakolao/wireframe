/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 18:19:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Adds x y z vertex (vector) posiion to a linked list of vertices.
*/

static t_list		*add_to_list(t_list *vertices, int x, int y, int z)
{
	t_list		*node;
	t_vector	*vertex;

	if (((vertex = ft_vector4_new(x, y, z)) == NULL || vertices == NULL))
	{
		if ((vertices = ft_lstnew(vertex, sizeof(*vertex))) == NULL)
			return (NULL);
	}
	else
	{
		if ((node = ft_lstnew(vertex, sizeof(*vertex))) == NULL)
			return (NULL);
		ft_lstappend(&vertices, node);
	}
	return (vertices);
}

/*
** Reads z from digit line using ft_atoi.
*/

static int			read_z_from_digit(char **line)
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
** Reads one line of map data and appends it to a linked list.
** x and x information is read here. Vertex count is calculated
** here as well.
*/

static t_list		*read_map_line(t_list *vertices, char *line, int y,
					t_map *map)
{
	int			x;
	int			z;

	x = 0;
	while (*line)
	{
		if (!(*line == ' ' || *line == '-' || ft_isdigit(*line)) &&
			log_error(ERR_READ, strerror(ERRNO_INVALID_INPUT)))
			return (NULL);
		if (ft_isdigit(*line) || *line == '-')
		{
			z = read_z_from_digit(&line);
			if ((vertices = add_to_list(vertices, x, y, z)) == NULL &&
				log_error("Failed t_list", strerror(ERRNO_INVALID_INPUT)))
				return (NULL);
			map->z_max = map->z_max >= z ? map->z_max : z;
			map->z_min = map->z_min <= z ? map->z_min : z;
			map->x_max = map->x_max >= x ? map->x_max : x;
			(map->vertex_count)++;
			x++;
		}
		else
			line++;
	}
	return (vertices);
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
	t_list	*vtx;

	y = 0;
	map->vertex_count = 0;
	map->x_max = 0;
	map->z_max = 0;
	map->z_min = 0;
	while ((ret = get_next_line(fd, &line)) == TRUE)
	{
		if ((vtx = read_map_line(vtx, line, y++, map)) == NULL)
			return (NULL);
		ft_strdel(&line);
	}
	if (ret == FALSE)
		map->y_max = y - 1;
	if ((((map->x = map->x_max) == 0 ||
			(map->y = map->y_max) == 0) && log_error(ERR_MAP, strerror(5))) ||
		(ret == -1 && log_perror("")) || (set_map_vertices(vtx, map) == FALSE &&
				log_error(ERR_CENTER, strerror(ERRNO_INVALID_INPUT))))
		return (NULL);
	ft_strdel(&line);
	return (map);
}

/*
** Serializes read data into map struct
*/

t_map				*serialize_map(char *filename)
{
	t_map		*map;
	int			fd;
	char		*error;

	if ((map = (t_map*)malloc(sizeof(*map))) == NULL ||
		((fd = open(filename, O_RDONLY)) == -1 && log_perror("")) ||
		(map = file_to_map(fd, map)) == NULL ||
		(map->center = ft_vector4_new(0, 0, 0)) == NULL ||
		(map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL ||
		(map->reset_rotation =
			ft_matrix_inverse_4x4(map->rotation)) == NULL ||
		(map->scale = ft_matrix_id(4, 4)) == NULL ||
		(map->reset_scale =
			ft_matrix_inverse_4x4(map->scale)) == NULL)
	{
		if ((error = ft_strjoin("Error reading map: ", filename)) == NULL)
			return (NULL);
		log_error(error, strerror(ERRNO_INVALID_INPUT));
		ft_strdel(&error);
		return (NULL);
	}
	map->name = filename;
	if (close(fd) == -1 && log_perror(""))
		return (NULL);
	return (map);
}
