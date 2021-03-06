/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:35:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:03:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_map_info				*map_info(t_scene *scene)
{
	t_map_info	*map_info;

	if ((map_info =
			(t_map_info*)malloc(sizeof(t_map_info))) == NULL ||
			(map_info->vertices =
				ft_itoa(scene->maps[scene->map_index]->vertex_count)) == NULL ||
			(map_info->x_min =
				ft_itoa(scene->maps[scene->map_index]->x_min)) == NULL ||
			(map_info->x_max =
				ft_itoa(scene->maps[scene->map_index]->x_max)) == NULL ||
			(map_info->y_min =
				ft_itoa(scene->maps[scene->map_index]->y_min)) == NULL ||
			(map_info->y_max =
				ft_itoa(scene->maps[scene->map_index]->y_max)) == NULL ||
			(map_info->z_min =
				ft_itoa(scene->maps[scene->map_index]->z_min)) == NULL ||
			(map_info->z_max =
				ft_itoa(scene->maps[scene->map_index]->z_max)) == NULL)
		return (NULL);
	return (map_info);
}

/*
** Renders a vector to UI to given position.
*/

void					draw_vector(t_scene *scene, t_vector *v,
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
** Draws vector (point) if it's screen position is witihn
** screen;
*/

void					draw_vector_if_within_screen(t_scene *scene,
						t_vector *p, t_vector *s)
{
	if (!screen_pt(p, scene, s))
		return ;
	s->v[0] += WIDTH / 2 - 40;
	s->v[1] += HEIGHT / 2;
	if (s->v[0] >= 0 && s->v[0] <= WIDTH &&
		s->v[1] >= 0 && s->v[1] <= HEIGHT)
		draw_vector(scene, p, s->v[0], s->v[1]);
}

/*
** Draws given int color into UI (R, G, B)
*/

void					draw_color_info(t_scene *scene, int color, int x, int y)
{
	char	*red;
	char	*green;
	char	*blue;
	char	*col;

	if ((red = ft_itoa(RED(color))) == NULL ||
		(green = ft_itoa(GREEN(color))) == NULL ||
		(blue = ft_itoa(BLUE(color))) == NULL ||
		(col = ft_strnew(256)) == NULL ||
		(col = ft_strcpy(col, "(")) == NULL ||
		(col = ft_strcat(col, red)) == NULL ||
		(col = ft_strcat(col, ", ")) == NULL ||
		(col = ft_strcat(col, green)) == NULL ||
		(col = ft_strcat(col, ", ")) == NULL ||
		(col = ft_strcat(col, blue)) == NULL ||
		(col = ft_strcat(col, ")")) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, x, y, UI_COLOR, col);
	ft_strdel(&col);
	ft_strdel(&red);
	ft_strdel(&green);
	ft_strdel(&blue);
}
