/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 11:08:07 by ohakola          ###   ########.fr       */
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
	char	*guide;

	if ((scene->show_guide && (guide = ft_strdup("USAGE Keys:\n"\
			"----------\nESC: Exit\n"
			"G: Toggle guide\n"
			"Left: Rotate map around y-\n"\
			"Right: Rotate map around y+\n"
			"Up: Rotate map around x+\n"
			"Down: Rotate map around x-\n"
			"W: Move forward\n"
			"S: Move backwards\nA: Strafe left\n"
			"D: Strafe right\nQ: Rotate map around z-\n"
			"E: Rotate map around z+\nC: Loop colors\n"
			"P: Loop perspective\nR: Reset\n"
			"1: zoom out by widening FoV\n"
			"2: zoom in by narrowing FoV\n"
			"Num 4: Turn camera left\n"
			"Num 6: Turn camera right\nNum 8: Turn camera up\n"
			"Num 2: Turn camera down\nNum +: Scale map up\n"
			"Num -: Scale map down\n")) == NULL) ||
		(!scene->show_guide && (guide = ft_strdup("USAGE Keys:\n"
			"----------\nESC: Exit\n"
			"G: Toggle guide")) == NULL))
		return (NULL);
	return (guide);
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
** Draw UI content to the window
*/

void				draw_ui(t_scene *scene)
{
	char	*mouse_g;
	char	*key_g;

	if ((mouse_g = mouse_guide(scene)) == NULL ||
		(key_g = key_guide(scene)) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, 20, UI_COLOR, "Camera xyz:");
	draw_vector(scene, scene->camera->position, 130, 20);
	draw_map_info(scene, WINDOW_WIDTH - 160, 20);
	draw_paragraph(scene, key_g, 10, 60);
	draw_paragraph(scene, mouse_g, 10, 550);
	ft_strdel(&mouse_g);
	ft_strdel(&key_g);
}
