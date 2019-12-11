/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 20:02:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_point		*new_point(int x, int y, int z)
{
	t_point	*p;

	if ((p = (t_point*)malloc(sizeof(*p))) == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

static t_canvas		*new_canvas(int width, int height)
{
	t_canvas	*c;

	if ((c = (t_canvas*)malloc(sizeof(*c))) == NULL)
		return (NULL);
	c->width = width;
	c->height = height;
	return (c);
}

static t_camera		*new_camera(t_point *position)
{
	t_camera	*camera;
	t_canvas	*canvas;
	t_rgb		*color;

	if ((camera = (t_camera*)malloc(sizeof(*camera))) == NULL || position == NULL)
		return (NULL);
	if ((canvas = new_canvas(2.0, 2.0)) == NULL)
		return (NULL);
	if ((color = ft_itorgb(MAP_COLOR)) == NULL)
		return (NULL);
	camera->position = position;
	camera->canvas = canvas;
	camera->color = color;
	camera->zoom = ZOOM;
	camera->view_matrix = scale_matrix(identity_matrix(), camera->zoom);
	return (camera);
}

static t_scene		*new_scene(t_map *map, t_camera *camera)
{
	t_scene	*scene;

	if ((scene = (t_scene*)malloc(sizeof(*scene))) == NULL)
		return (NULL);
	scene->camera = camera;
	scene->map = map;
	return (scene);
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_wdw;
	t_camera	*camera;
	t_map		*map;
	t_scene		*scene;

	mlx = mlx_init();
	mlx_wdw = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Wireframe");

	map = NULL;
	camera = NULL;
	if (argc > 1)
	{
		if ((map = serialize(argv[1])) == NULL)
		{
			log_error(ERR_SERIALIZATION, strerror(ERRNO_INVALID_INPUT));
			return (0);
		}
		log_map(map);
	}
	if ((camera = new_camera(new_point(0.0, 0.0, -10.0))) == NULL)
		return (0);
	if ((scene = new_scene(map, camera)) == NULL)
		return (0);
	mlx_key_hook(mlx_wdw, handle_key_events, scene);
	draw(mlx, mlx_wdw, scene);
	mlx_loop(mlx);
	return (0);
}