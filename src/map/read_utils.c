/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:26:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/29 14:41:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Adds x y z vertex (vector) posiion to a linked list of vertices.
*/

t_list		*add_to_list(t_list *vertices, int x, int y, int z)
{
	t_list		*node;
	t_vector	*vertex;

	if ((vertex = ft_vector4_new(x, y, z)) == NULL)
		return (NULL);
	if (vertices == NULL)
	{
		if ((vertices = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
		vertices->content = vertex;
		vertices->content_size = sizeof(*vertex);
	}
	else
	{
		if ((node = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
		node->content = vertex;
		node->content_size = sizeof(*vertex);
		ft_lstappend(&vertices, node);
	}
	return (vertices);
}

/*
** Reads z from digit line using ft_atoi.
*/

int			read_z_from_digit(char **line)
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
