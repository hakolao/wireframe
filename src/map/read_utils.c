/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:26:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/29 12:28:57 by ohakola          ###   ########.fr       */
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
