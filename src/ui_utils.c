/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:35:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 20:03:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Returns key usage guide
*/

char			*key_guide(void)
{
	char	*guide;

	if ((guide = ft_strdup("UI_COLOR, USAGE Keys:\n\
			----------\nESC: Exit\n\
			Left: Rotate map around y-\n\
			Right: Rotate map around y+\n\
			Up: Rotate map around x+\n\
			Down: Rotate map around x-\n\
			W: Move forward\n\
			D: Move backwards\nA: Strafe left\n\
			D: Strafe right\n\
			Q: Rotate map around z-\n\
			E: Rotate map around z+\n\
			P: Loop perspective\nR: Reset\n\
			1: zoom out by widening FoV\n\
			2: zoom in by narrowing FoV\n\
			Num 4: Turn camera left\n\
			Num 6: Turn camera right\n\
			Num 8: Turn camera up\n\
			Num 2: Turn camera down\n\
			Num +: Scale map up\n\
			Num -: Scale map down\n\
			")) == NULL)
		return (NULL);
	return (guide);
}

/*
** Returns mouse usage guide
*/

char			*mouse_guide(void)
{
	char	*guide;

	if ((guide = ft_strdup("USAGE Mouse:\n\
				----------\n\
				Scroll up: Scale map z up\n\
				Scroll down: Scale map z down\n\
				Hold left mouse & move: Rotate camera\n\
				Hold right mouse & move: Rotate map")) == NULL)
		return (NULL);
	return (guide);
}

/*
** Draws a guide of key usage into screen
*/

void			draw_key_guide(t_scene *scene, int xpos, int ypos)
{
	char	*keys;
	char	**key_text;
	int		i;

	if ((keys = key_guide()) == NULL ||
		(key_text = ft_strsplit(keys, '\n')) == NULL)
		return ;
	ft_strdel(&keys);
	i = 0;
	while (key_text[i])
	{
		mlx_string_put(scene->mlx, scene->mlx_wdw, xpos,
			ypos + i * 20, UI_COLOR, key_text[i]);
		ft_strdel(&key_text[i++]);
	}
	free(key_text);
}

/*
** Draws a guide of mouse usage into screen
*/

void			draw_mouse_guide(t_scene *scene, int xpos, int ypos)
{
	char	*mouses;
	char	**mouse_text;
	int		i;

	if ((mouses = mouse_guide()) == NULL ||
		(mouse_text = ft_strsplit(mouses, '\n')) == NULL)
		return ;
	ft_strdel(&mouses);
	i = 0;
	while (mouse_text[i])
	{
		mlx_string_put(scene->mlx, scene->mlx_wdw, xpos,
			ypos + i * 20, UI_COLOR, mouse_text[i]);
		ft_strdel(&mouse_text[i++]);
	}
	free(mouse_text);
}
