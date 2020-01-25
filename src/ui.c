/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 17:57:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			vector_to_ui(t_scene *scene, t_vector *v,
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

static void			map_info(t_scene *scene, t_map_info *map,
					int xpos, int ypos)
{
	void	*mlx;
	void	*mlx_wdw;

	mlx = scene->mlx;
	mlx_wdw = scene->mlx_wdw;
	mlx_string_put(mlx, mlx_wdw, xpos + 100, ypos, UI_COLOR, map->vertices);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 20, UI_COLOR, "x_min: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 20, UI_COLOR, map->x_min);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 40, UI_COLOR, "x_max: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 40, UI_COLOR, map->x_max);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 60, UI_COLOR, "y_min: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 60, UI_COLOR, map->y_min);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 80, UI_COLOR, "y_max: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 80, UI_COLOR, map->y_max);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 100, UI_COLOR, "z_min: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 100, UI_COLOR, map->z_min);
	mlx_string_put(mlx, mlx_wdw, xpos, ypos + 120, UI_COLOR, "z_max: ");
	mlx_string_put(mlx, mlx_wdw, xpos + 70, ypos + 120, UI_COLOR, map->z_max);
	ft_strdel(&map->vertices);
	ft_strdel(&map->x_min);
	ft_strdel(&map->x_max);
	ft_strdel(&map->y_min);
	ft_strdel(&map->y_max);
	ft_strdel(&map->z_min);
	ft_strdel(&map->z_max);
}

static void			draw_map_info(t_scene *scene, int xpos, int ypos)
{
	t_map_info	map;

	mlx_string_put(scene->mlx, scene->mlx_wdw, xpos, ypos,
		UI_COLOR, "Vertices:");
	if ((map.vertices = ft_itoa(scene->map->vertex_count)) == NULL ||
		(map.x_min = ft_itoa(scene->map->x_min)) == NULL ||
		(map.x_max = ft_itoa(scene->map->x_max)) == NULL ||
		(map.y_min = ft_itoa(scene->map->y_min)) == NULL ||
		(map.y_max = ft_itoa(scene->map->y_max)) == NULL ||
		(map.z_min = ft_itoa(scene->map->z_min)) == NULL ||
		(map.z_max = ft_itoa(scene->map->z_max)) == NULL)
		return ;
	map_info(scene, &map, xpos, ypos);
}

void				draw_ui(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, 20, UI_COLOR, "Camera xyz:");
	vector_to_ui(scene, scene->camera->position, 130, 20);
	draw_map_info(scene, 10, 60);
}
