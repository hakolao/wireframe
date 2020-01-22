/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 16:41:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

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

static int			read_z_from_digit(char **line)
{
	int	z;

	z = ft_atoi(*line);
	while (**line && ft_isdigit(**line))
		(*line)++;
	while (**line && !ft_isdigit(**line))
		(*line)++;
	return (z);
}

static t_list		*read_map_line(t_list *vertices, char *line, int y,
					t_map *map)
{
	int			x;
	int			z;

	x = 0;
	while (*line)
	{
		if (!(*line == ' ' || *line == '-' || ft_isdigit(*line)) &&
			log_error(ERR_INVALID_INPUT, strerror(ERRNO_INVALID_INPUT)))
			return (NULL);
		if (ft_isdigit(*line))
		{
			z = read_z_from_digit(&line);
			if ((vertices = add_to_list(vertices, x, y, z)) == NULL)
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

static t_map		*file_to_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		y;
	t_list	*vertex_list;

	y = 0;
	map->vertex_count = 0;
	map->x_max = 0;
	map->z_max = 0;
	while ((ret = get_next_line(fd, &line)) == TRUE)
	{
		if ((vertex_list = read_map_line(vertex_list, line, y++, map)) == NULL)
			return (NULL);
		ft_strdel(&line);
	}
	if (ret == FALSE)
		map->y_max = y - 1;
	map->x = map->x_max;
	map->y = map->y_max;
	map->z = map->z_max - map->z_min;
	if ((ret == -1 && log_perror("")) ||
		center_and_set_map_vertices(vertex_list, map) == FALSE)
		return (NULL);
	ft_strdel(&line);
	return (map);
}

t_map				*serialize(char *filename)
{
	t_map		*map;
	int			fd;

	if ((map = (t_map*)malloc(sizeof(*map))) == NULL)
		return (NULL);
	if ((fd = open(filename, O_RDONLY)) == -1 && log_perror(""))
		return (NULL);
	if ((map = file_to_map(fd, map)) == NULL ||
		(map->center = ft_vector4_new(0, 0, 0)) == NULL ||
		(map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL ||
		(map->color = ft_itorgb(MAP_COLOR)) == NULL)
		return (NULL);
	close(fd);
	return (map);
}
