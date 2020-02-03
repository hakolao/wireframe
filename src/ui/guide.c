/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:09:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/03 14:03:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char			*key_guide(t_scene *scene)
{
	char	*final_guide;
	char	*guide;
	char	*map_loop;

	if ((scene->show_guide && (guide = ft_strdup("USAGE Keys:\n"
			"----------\nESC: Exit\nG: Toggle guide\n"
			"Left: Rotate map y-\nRight: Rotate map y+\n"
			"Up: Rotate map x+\nDown: Rotate map x-\nW: Move forward\n"
			"S: Move backwards\nA: Strafe left\nD: Strafe right\n"
			"Q: Rotate map z-\nE: Rotate map z+\nC: Loop map color\n"
			"B: Loop bg color\nP: Loop perspective\nR: Reset\n"
			"O: Show coords\n1: zoom -\n2: zoom +\nNum 4: Turn left\n"
			"Num 6: Turn right\nNum 8: Turn up\nNum 2: Turn down\n"
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

char			*mouse_guide(t_scene *scene)
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

void			draw_paragraph(t_scene *scene, char *text, int xpos,
				int ypos)
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
