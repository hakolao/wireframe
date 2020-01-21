/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/21 15:04:31 by ohakola          ###   ########.fr       */
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

void				draw_ui(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, 20, UI_COLOR, "Camera xyz:");
	vector_to_ui(scene, scene->camera->position, 10, 35);
}
