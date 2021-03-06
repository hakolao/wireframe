/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 16:35:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			draw_map_info(t_scene *scene, int xpos, int ypos)
{
	t_map_info	*map_i;
	char		*info_text;

	if ((map_i = map_info(scene)) == NULL ||
		(info_text = ft_strnew(256)) == NULL ||
		(info_text = ft_strcpy(info_text, "Vertices: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->vertices)) == NULL ||
		(info_text = ft_strcat(info_text, "\nx_min: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->x_min)) == NULL ||
		(info_text = ft_strcat(info_text, "\nx_max: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->x_max)) == NULL ||
		(info_text = ft_strcat(info_text, "\ny_min: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->y_min)) == NULL ||
		(info_text = ft_strcat(info_text, "\ny_max: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->y_max)) == NULL ||
		(info_text = ft_strcat(info_text, "\nz_min: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->z_min)) == NULL ||
		(info_text = ft_strcat(info_text, "\nz_max: ")) == NULL ||
		(info_text = ft_strcat(info_text, map_i->x_max)) == NULL)
		return ;
	draw_paragraph(scene, info_text, xpos, ypos);
	free_map_info(map_i);
	ft_strdel(&info_text);
}

static void			draw_multi_map_info(t_scene *scene, char *read_maps,
					char *map_index)
{
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, HEIGHT - 90,
		UI_COLOR, "Total maps:");
	mlx_string_put(scene->mlx, scene->mlx_wdw, 130, HEIGHT - 90,
		UI_COLOR, read_maps);
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, HEIGHT - 70,
		UI_COLOR, "Map index:");
	mlx_string_put(scene->mlx, scene->mlx_wdw, 130, HEIGHT - 70,
		UI_COLOR, map_index);
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, HEIGHT - 50,
		UI_COLOR, "Map:");
	mlx_string_put(scene->mlx, scene->mlx_wdw, 60, HEIGHT - 50,
		UI_COLOR, scene->maps[scene->map_index]->name);
}

static void			draw_height_color_info(t_scene *scene, int x, int y)
{
	int			top_col;
	int			mid_col;
	int			bot_col;
	t_map		*map;

	map = scene->maps[scene->map_index];
	top_col = map_color(&(t_vector){.v =
		(double[]){0, 0, map->z_max, 1}, .size = 4}, scene);
	mid_col = map_color(&(t_vector){.v =
		(double[]){0, 0, 0, 1}, .size = 4}, scene);
	bot_col = map_color(&(t_vector){.v =
		(double[]){0, 0, map->z_min, 1}, .size = 4}, scene);
	mlx_string_put(scene->mlx, scene->mlx_wdw, x, y, UI_COLOR, "Top RGB:");
	draw_color_info(scene, top_col, x + 120, y);
	mlx_string_put(scene->mlx, scene->mlx_wdw, x, y + 20,
		UI_COLOR, "Mid RGB:");
	draw_color_info(scene, mid_col, x + 120, y + 20);
	mlx_string_put(scene->mlx, scene->mlx_wdw, x, y + 40,
		UI_COLOR, "Bottom RGB:");
	draw_color_info(scene, bot_col, x + 120, y + 40);
}

static void			draw_corner_coords(t_scene *scene)
{
	t_map		*map;

	map = scene->maps[scene->map_index];
	if (!scene->show_coords)
		return ;
	draw_vector_if_within_screen(scene, map->vertices[0],
		&(t_vector){.v = (double[4]){0}, .size = 4});
	draw_vector_if_within_screen(scene, map->vertices[map->x],
		&(t_vector){.v = (double[4]){0}, .size = 4});
	draw_vector_if_within_screen(scene,
		map->vertices[map->vertex_count - map->x - 1],
		&(t_vector){.v = (double[4]){0}, .size = 4});
	draw_vector_if_within_screen(scene,
		map->vertices[map->vertex_count - 1],
		&(t_vector){.v = (double[4]){0}, .size = 4});
}

void				draw_ui(t_scene *scene)
{
	char	*mouse_g;
	char	*key_g;
	char	*read_maps;
	char	*map_index;

	if ((mouse_g = mouse_guide(scene)) == NULL ||
		(key_g = key_guide(scene)) == NULL ||
		(read_maps = ft_itoa(scene->map_count)) == NULL ||
		(map_index = ft_itoa(scene->map_index)) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, 20, UI_COLOR, "Camera xyz:");
	draw_vector(scene, scene->camera->position, 130, 20);
	draw_map_info(scene, WIDTH - 200, 20);
	draw_paragraph(scene, key_g, 10, 60);
	draw_paragraph(scene, mouse_g, 10, 650);
	draw_multi_map_info(scene, read_maps, map_index);
	draw_height_color_info(scene, WIDTH - 300, HEIGHT - 90);
	draw_corner_coords(scene);
	ft_strdel(&mouse_g);
	ft_strdel(&key_g);
	ft_strdel(&read_maps);
	ft_strdel(&map_index);
}
