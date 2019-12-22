/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:35 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/22 15:29:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_list		*add_to_list(t_list *vertices, int x, int y, int z)
{
	t_list		*node;
	t_vector	*vertex;

	if (((vertex = ft_vector4_new(x, y, z)) == NULL || vertices == NULL) &&
		(vertices = ft_lstnew(vertex, sizeof(*vertex))) == NULL)
		return (NULL);
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
			map->x_max = map->x_max >= x ? map->x_max : x;
			(map->vertex_count)++ && x++;	
		}
		else
			line++;
	}
	return (vertices);
}

t_vector			*map_center(t_map *map)
{
	t_vector	*center;
	double		res[3];
	size_t		i;

	i = 0;
	while (i < map->vertex_count)
	{
		res[0] += map->vertices[i]->v[0];
		res[1] += map->vertices[i]->v[1];
		res[2] += map->vertices[i]->v[2];
		i++;
	}
	res[0] = res[0] / map->vertex_count;
	res[1] = res[1] / map->vertex_count;
	res[2] = res[2] / map->vertex_count;
	if ((center = ft_vector4_new(res[0], res[1], res[2])) == NULL)
		return (NULL);
	return (center);
}

static void			set_vertices_to_map(t_list *vertices, t_map *map)
{
	t_vector 	**vs;
	size_t		i;
	
	if ((vs = (t_vector**)malloc(sizeof(*vs) * map->vertex_count)) == NULL)
		return ;
	i = 0;
	while (vertices)
	{
		vs[i] = (t_vector*)(vertices->content);
		vertices = vertices->next;
		i++;
	}
	map->vertices = vs;
	free(vertices);
}

static t_map		*file_to_map(int fd, t_map *map)
{
	char	*line;
	int		ret;
	int		y;
	t_list	*vertices;

	line = NULL;
	vertices = NULL;
	y = 0;
	map->vertex_count = 0;
	map->x_max = 0;
	map->z_max = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((vertices = add_vertices(vertices, line, y++, map)) == NULL)
			return (NULL);
		ft_strdel(&line);
	}
	if (ret == 0)
		map->y_max = y - 1;
	if (ret == -1 && log_perror(""))
		return (NULL);
	set_vertices_to_map(vertices, map);
	return (map);
}

t_map				*serialize(char *filename)
{
	t_map		*map;
	t_vector	*center;
	int			fd;

	if ((map = (t_map*)malloc(sizeof(*map))) == NULL)
		return (NULL);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror("");
		return (NULL);
	}
	if ((map = file_to_map(fd, map)) == NULL)
		return (NULL);
	if ((center = map_center(map)) == NULL)
		return (NULL);
	map->center = center;
	map->scale = WINDOW_WIDTH / map->x_max * 0.5;
	close(fd);
	return (map);
}