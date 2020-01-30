/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:09:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 22:10:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Returns key usage guide
*/

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
			"B: Loop bg color\nP: Loop perspective\nR: Reset\n1: zoom -\n"
			"2: zoom +\nNum 4: Turn camera left\nNum 6: Turn camera right\n"
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
