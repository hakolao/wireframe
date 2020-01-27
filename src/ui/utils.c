/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:35:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 12:14:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Free map information struct
*/

void					free_map_info(t_map_info *map)
{
	ft_strdel(&map->vertices);
	ft_strdel(&map->x_min);
	ft_strdel(&map->x_max);
	ft_strdel(&map->y_min);
	ft_strdel(&map->y_max);
	ft_strdel(&map->z_min);
	ft_strdel(&map->z_max);
	free(map);
}

/*
** Set map information
*/

t_map_info				*map_info(t_scene *scene)
{
	t_map_info	*map_info;

	if ((map_info =
			(t_map_info*)malloc(sizeof(t_map_info))) == NULL ||
			(map_info->vertices = ft_itoa(scene->map->vertex_count)) == NULL ||
			(map_info->x_min = ft_itoa(scene->map->x_min)) == NULL ||
			(map_info->x_max = ft_itoa(scene->map->x_max)) == NULL ||
			(map_info->y_min = ft_itoa(scene->map->y_min)) == NULL ||
			(map_info->y_max = ft_itoa(scene->map->y_max)) == NULL ||
			(map_info->z_min = ft_itoa(scene->map->z_min)) == NULL ||
			(map_info->z_max = ft_itoa(scene->map->z_max)) == NULL)
		return (NULL);
	return (map_info);
}

/*
** Renders a vector to UI to given position.
*/

void				draw_vector(t_scene *scene, t_vector *v,
					int xpos, int ypos)
{
	char	*vectorstr;
	char	*x;
	char	*y;
	char	*z;

	if ((x = ft_itoa(v->v[0])) == NULL ||
		(y = ft_itoa(v->v[1])) == NULL ||
		(z = ft_itoa(v->v[2])) == NULL)
		return ;
	if ((vectorstr = ft_strnew(256)) == NULL ||
		ft_strcpy(vectorstr, x) == NULL ||
		ft_strcat(vectorstr, ", ") == NULL ||
		ft_strcat(vectorstr, y) == NULL ||
		ft_strcat(vectorstr, ", ") == NULL ||
		ft_strcat(vectorstr, z) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, xpos, ypos, UI_COLOR, vectorstr);
	ft_strdel(&vectorstr);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
}

/*
** Draws a paragraph of key usage into screen
*/

void			draw_paragraph(t_scene *scene, char *text, int xpos, int ypos)
{
	char	**split_text;
	int		i;

	if (!text || (split_text = ft_strsplit(text, '\n')) == NULL)
		return ;
	i = 0;
	while (split_text[i])
	{
		mlx_string_put(scene->mlx, scene->mlx_wdw, xpos,
			ypos + i * 20, UI_COLOR, split_text[i]);
		ft_strdel(&split_text[i++]);
	}
	free(split_text);
}
