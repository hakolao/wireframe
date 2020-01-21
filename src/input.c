/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/21 13:56:59 by ohakola          ###   ########.fr       */
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

static t_list		*add_vertices(t_list *vertices, char *line, int y, t_map *map)
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
			z = ft_atoi(line);
			while (*line && ft_isdigit(*line))
				line++;
			while (*line && !ft_isdigit(*line))
				line++;
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

static int			set_vertex_limits(t_map *map, t_vector *vertex)
{
	map->x_max = map->x_max >= vertex->v[0] ? map->x_max : vertex->v[0];
	map->x_min = map->x_min <= vertex->v[0] ? map->x_min : vertex->v[0];
	map->y_max = map->y_max >= vertex->v[1] ? map->y_max : vertex->v[1];
	map->y_min = map->y_min <= vertex->v[1] ? map->y_min : vertex->v[1];
	map->z_max = map->z_max >= vertex->v[2] ? map->z_max : vertex->v[2];
	map->z_min = map->z_min <= vertex->v[2] ? map->z_min : vertex->v[2];
	return (1);
}

static int			center_and_set_vertices(t_list *vtx_lst, t_map *map)
{
	t_vector 	**vs;
	t_vector	*shift;
	size_t		i;
	
	if ((vs = (t_vector**)malloc(sizeof(*vs) * map->vertex_count)) == NULL ||
		(shift = ft_vector4_new(
			-map->x_max / 2, -map->y_max / 2, -(map->z_max - map->z_min) / 2)
			) == NULL)
		return (0);
	if (!(map->x_max = 0) && !(map->x_min = 0) && !(map->y_max = 0) &&
	!(map->y_min = 0) && !(map->z_max = 0) && !(map->z_min = 0))
		;
	i = 0;
	while (vtx_lst)
	{
		vs[i] = (t_vector*)(vtx_lst->content);
		if (ft_vector_add(vs[i], shift, vs[i]) == FALSE ||
			set_vertex_limits(map, vs[i]) == FALSE)
			return (0);
		vs[i++]->v[3] = 1;
		vtx_lst = vtx_lst->next;
	}
	map->vertices = vs;
	ft_vector_free(shift);
	free(vtx_lst);
	return (1);
}

static t_map		*file_to_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		y;
	t_list	*vertex_list;

	line = NULL;
	vertex_list = NULL;
	y = 0;
	map->vertex_count = 0;
	map->x_max = 0;
	map->z_max = 0;
	while ((ret = get_next_line(fd, &line)) == TRUE)
	{
		if ((vertex_list = add_vertices(vertex_list, line, y++, map)) == NULL)
			return (NULL);
		ft_strdel(&line);
	}
	if (ret == FALSE)
		map->y_max = y - 1;
	map->x = map->x_max;
	map->y = map->y_max;
	map->z = map->z_max - map->z_min;
	if ((ret == -1 && log_perror("")) ||
		center_and_set_vertices(vertex_list, map) == FALSE)
		return (NULL);
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
		(map->rotation = ft_rotation_matrix(0, 0, 0)) == NULL)
		return (NULL);
	close(fd);
	return (map);
}
