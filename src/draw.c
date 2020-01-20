/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/20 17:52:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

t_vector			*screen_pt(t_vector *point, t_scene *scene)
{
	t_vector	*on_screen;

	if ((on_screen = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(scene->camera->transform, point, on_screen) == FALSE)
		return (NULL);
	on_screen->v[0] /= on_screen->v[3];
	on_screen->v[1] /= on_screen->v[3];
	on_screen->v[2] /= on_screen->v[3];
	on_screen->v[3] /= on_screen->v[3];
	return (on_screen);
}

static int			in_front_of_camera(t_vector *p1, t_vector *p2, t_camera *camera)
{
	t_vector	*c1;
	t_vector	*c2;
	int			ret;

	if ((c1 = ft_vector_new(4)) == NULL ||
		(c2 = ft_vector_new(4)) == NULL ||
		ft_matrix_mul_vector(camera->view, p1, c1) == FALSE ||
		ft_matrix_mul_vector(camera->view, p2, c2) == FALSE)
		return (0);
	ret = c1->v[2] > 0 && c2->v[2] > 0;
	ft_vector_free(c1);
	ft_vector_free(c2);
	return (ret);
}

static void			connect_points(t_vector *p1, t_vector *p2, t_scene *scene, int color){
	t_vector 	*s1;
	t_vector	*s2;
	
	if (!in_front_of_camera(p1, p2, scene->camera))
		return ;
	if (((s1 = screen_pt(p1, scene)) == NULL ||
			(s2 = screen_pt(p2, scene)) == NULL) &&
			log_error("Something failed in point_to_screen.", ""))
			exit(1);
	draw_line(s1, s2, color, scene);
}

static void			draw_map(t_scene *scene)
{
	int			color;
	size_t		i;
	
	color = ft_rgbtoi(*(scene->camera->color));
	i = -1;
	while (++i < scene->map->vertex_count - 1)
	{
		if ((i + 1) % (scene->map->x + 1) != 0)
			connect_points(scene->map->vertices[i], scene->map->vertices[i + 1], scene, color);
		if (i < scene->map->vertex_count - scene->map->x - 1)
			connect_points(scene->map->vertices[i], scene->map->vertices[i + 1 + scene->map->x], scene, color);
	}
}

static void			vector_to_ui(t_scene *scene, t_vector *v, int xpos, int ypos)
{
	char x[50];
	char y[50];
	char z[50];
	char *vectorstr;

	ft_strcpy(x, ft_itoa(v->v[0]));
	ft_strcpy(y, ft_itoa(v->v[1]));
	ft_strcpy(z, ft_itoa(v->v[2]));
	if ((vectorstr = ft_strjoin(x, ", ")) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, y)) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, ", ")) == NULL ||
		(vectorstr = ft_strjoin(vectorstr, z)) == NULL)
		return ;
	mlx_string_put(scene->mlx, scene->mlx_wdw, xpos, ypos, UI_COLOR, vectorstr);
}

static void			draw_ui(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->mlx_wdw, 10, 20, UI_COLOR, "Camera position:");
	vector_to_ui(scene, scene->camera->position, 10, 35);
}

void				draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	draw_map(scene);
	draw_ui(scene);
}
