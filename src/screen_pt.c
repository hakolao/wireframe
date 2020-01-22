/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_pt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:26:52 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 16:36:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector			*screen_pt(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(
			scene->camera->transform, point, on_screen) == FALSE)
		return (NULL);
	on_screen->v[0] /= on_screen->v[3];
	on_screen->v[1] /= on_screen->v[3];
	on_screen->v[2] /= on_screen->v[3];
	on_screen->v[3] /= on_screen->v[3];
	return (on_screen);
}

static int			in_front_of_camera(t_vector *p1, t_vector *p2,
					t_camera *camera)
{
	t_vector	*c1;
	t_vector	*c2;
	int			ret;

	if ((c1 = ft_vector_new(4)) == NULL ||
		(c2 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(camera->view, p1, c1) == FALSE ||
		ft_matrix_mul_vector(camera->view, p2, c2) == FALSE)
		return (0);
	ret = c1->v[2] > 0.5 && c2->v[2] > 0.5;
	ft_vector_free(c1);
	ft_vector_free(c2);
	return (ret);
}

void				connect_points(t_vector *p1, t_vector *p2,
					t_scene *scene, int color)
{
	t_vector	*s1;
	t_vector	*s2;

	if (!in_front_of_camera(p1, p2, scene->camera))
		return ;
	if (((s1 = screen_pt(p1, scene)) == NULL ||
		(s2 = screen_pt(p2, scene)) == NULL) &&
		log_error("Something failed in point_to_screen.", ""))
		exit(1);
	s1->v[0] = (s1->v[0] * ASPECT_RATIO);
	s2->v[0] = (s2->v[0] * ASPECT_RATIO);
	draw_line(s1, s2, color, scene);
	ft_vector_free(s1);
	ft_vector_free(s2);
}
