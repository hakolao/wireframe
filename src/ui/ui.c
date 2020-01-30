/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 19:05:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Generates map information struct and renders that information to UI
*/

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

/*
** Returns key usage guide
*/

static char			*key_guide(t_scene *scene)
{
	char	*final_guide;
	char	*guide;
	char	*map_loop;

	if ((scene->show_guide && (guide = ft_strdup("USAGE Keys:\n"
			"----------\nESC: Exit\nG: Toggle guide\n"
			"Left: Rotate map around y-\n"\
			"Right: Rotate map around y+\nUp: Rotate map around x+\n"
			"Down: Rotate map around x-\nW: Move forward\n"
			"S: Move backwards\nA: Strafe left\nD: Strafe right\n"
			"Q: Rotate map around z-\nE: Rotate map around z+\nC: Loop colors\n"
			"P: Loop perspective\nR: Reset\n1: zoom out\n2: zoom in\n"
			"Num 4: Turn camera left\nNum 6: Turn camera right\n"
			"Num 8: Turn camera up\nNum 2: Turn camera down\n"
			"Num +: Scale map up\nNum -: Scale map down\n")) == NULL) ||
		(!scene->show_guide && (guide = ft_strdup("USAGE Keys:\n"
			"----------\nESC: Exit\n"
			"G: Toggle guide")) == NULL) ||
		!(map_loop = (scene->map_count > 1 ?
			ft_strdup("\nTab/(Shift+Tab): Switch map") : ft_strdup(""))) ||
		(final_guide = ft_strjoin(guide, map_loop)) == NULL)
		return (NULL);
	ft_strdel(&guide);
	ft_strdel(&map_loop);
	return (final_guide);
}

/*
** Returns mouse usage guide
*/

static char			*mouse_guide(t_scene *scene)
{
	char	*guide;

	if ((scene->show_guide && (guide = ft_strdup("USAGE Mouse:\n"
			"----------\n"
			"Scroll up: Scale map z up\n"
			"Scroll down: Scale map z down\n"
			"Hold left mouse & move: Rotate camera\n"
			"Hold right mouse & move: Rotate map")) == NULL) ||
		(!scene->show_guide && (guide = ft_strdup("")) == NULL))
		return (NULL);
	return (guide);
}

/*
** Draw multiple map info
*/

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

/*
** Draw UI content to the window
*/

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
	draw_map_info(scene, WIDTH - 160, 20);
	draw_paragraph(scene, key_g, 10, 60);
	draw_paragraph(scene, mouse_g, 10, 600);
	draw_multi_map_info(scene, read_maps, map_index);
	ft_strdel(&mouse_g);
	ft_strdel(&key_g);
	ft_strdel(&read_maps);
	ft_strdel(&map_index);
}
