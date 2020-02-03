/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:04:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/02/02 21:22:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Calculates screen space coordinates for triangle points
** And adjusts them to the middle of the screen.
*/

static void		set_triangle_screen_pts(t_triangle *triangle, t_vector *s1,
				t_vector *s2, t_vector *s3)
{
	if ((!screen_pt(triangle->ab->point1, triangle->ab->scene, s1) ||
		!screen_pt(triangle->ab->point2, triangle->ab->scene, s2) ||
		!screen_pt(triangle->bc->point2, triangle->bc->scene, s3)) &&
			log_err("Something failed in set_triangle_screen_pts.", ""))
		exit(1);
	s1->v[0] += WIDTH / 2;
	s1->v[1] += HEIGHT / 2;
	s2->v[0] += WIDTH / 2;
	s2->v[1] += HEIGHT / 2;
	s3->v[0] += WIDTH / 2;
	s3->v[1] += HEIGHT / 2;
	triangle->ab->screen1 = s1;
	triangle->ab->screen2 = s2;
	triangle->bc->screen1 = s2;
	triangle->bc->screen2 = s3;
	triangle->ca->screen1 = s3;
	triangle->ca->screen2 = s1;
}

/*
** Calculates screen points for triangles that are in front of camera.
** Then connects those edges.
*/

static void		connect_triangle_edges(t_edge *ab, t_edge *bc, t_edge *ca)
{
	t_triangle	triangle;

	if (!in_front_of_camera(ab->point1, ab->scene->camera) ||
		!in_front_of_camera(ab->point2, ab->scene->camera) ||
		!in_front_of_camera(bc->point2, ab->scene->camera))
		return ;
	triangle = (t_triangle){.ab = ab, .bc = bc, .ca = ca};
	set_triangle_screen_pts(&triangle,
		&(t_vector){.v = (double[4]){0}, .size = 4},
		&(t_vector){.v = (double[4]){0}, .size = 4},
		&(t_vector){.v = (double[4]){0}, .size = 4});
	connect_edge(ab);
	connect_edge(bc);
	connect_edge(ca);
}

/*
** Sets color values based on original vertices
** then tries to connect edges.
*/

static void		set_and_connect_triangle(t_edge *ab, t_edge *bc, t_edge *ca)
{
	t_scene	*scene;

	scene = ab->scene;
	if (!ft_matrix_mul_vector(scene->maps[scene->map_index]->reset_rotation,
							  ab->point1, ab->original1) ||
		!ft_matrix_mul_vector(scene->maps[scene->map_index]->reset_rotation,
							  ab->point2, ab->original2) ||
		!ft_matrix_mul_vector(scene->maps[scene->map_index]->reset_rotation,
							  bc->point2, bc->original2))
		return ;
	bc->original1 = ab->original2;
	ca->original1 = bc->original2;
	ca->original2 = ab->original1;
	ab->color_start = map_color(ab->original1, ab->scene);
	ab->color_end = map_color(ab->original2, ab->scene);
	bc->color_start = map_color(bc->original1, bc->scene);
	bc->color_end = map_color(bc->original2, bc->scene);
	ca->color_start = map_color(ca->original1, ca->scene);
	ca->color_end = map_color(ca->original2, ca->scene);
	connect_triangle_edges(ab, bc, ca);
}

/*
** Creates edge structs, sets their values & connects edges
*/

static void		draw_triangle(t_scene *scene, t_vector *a,
				t_vector *b, t_vector *c)
{
	t_edge	ab;
	t_edge	bc;
	t_edge	ca;

	ab = (t_edge){
		.scene = scene, .point1 = a, .point2 = b,
		.screen1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.screen2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.color_start = 0, .color_end = 0};
	bc = (t_edge){.scene = scene, .point1 = b, .point2 = c,
		.screen1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.screen2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.color_start = 0, .color_end = 0};
	ca = (t_edge){.scene = scene,.point1 = c, .point2 = a,
		.screen1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.screen2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original1 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.original2 = &(t_vector){.v = (double[4]){0}, .size = 4},
		.color_start = 0, .color_end = 0};
	set_and_connect_triangle(&ab, &bc, &ca);
}

/*
** Map vertex drawing algorithm to connect each vertex correctly
** to screen. Each position is connected as triangles
** A->C, C->B, B->A, A->D, D->C, C->A
*/

void			draw_map_on_frame(t_scene *scene)
{
	size_t			i;

	i = -1;
	while (++i < scene->maps[scene->map_index]->vertex_count -
			scene->maps[scene->map_index]->x - 2)
	{
		if ((i + 1) % (scene->maps[scene->map_index]->x + 1) != 0)
		{
			draw_triangle(scene,
				scene->maps[scene->map_index]->vertices[
					i + 2 + scene->maps[scene->map_index]->x],
				scene->maps[scene->map_index]->vertices[i + 1],
				scene->maps[scene->map_index]->vertices[i]);
			draw_triangle(scene,
				scene->maps[scene->map_index]->vertices[i],
				scene->maps[scene->map_index]->vertices[
					i + 1 + scene->maps[scene->map_index]->x],
				scene->maps[scene->map_index]->vertices[
					i + 2 + scene->maps[scene->map_index]->x]);
		}
	}
}
