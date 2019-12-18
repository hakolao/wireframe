/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/18 16:03:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define UI_VERTICAL_WIDTH 200
# define UI_HORIZONTAL_HEIGHT 100
# define VIEW_WIDTH WINDOW_WIDTH - UI_VERTICAL_WIDTH
# define VIEW_HEIGHT WINDOW_HEIGHT - UI_HORIZONTAL_HEIGHT

# define ZOOM 1

# define ERR_INVALID_INPUT "Lines must "\
						"consist of spaces & numbers."
# define ERR_SERIALIZATION "Input serialization failed."
# define ERRNO_INVALID_INPUT 5

# define KEY_ESC 53

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libmatrix/libmatrix.h"

# define MAP_COLOR ft_rgbtoi(0, 255, 0)

typedef struct		s_map
{
	t_list			*vertices;
	int				vertex_count;
	double			x_max;
	double			y_max;
	double			z_max;
}					t_map;

typedef struct 		s_camera
{
	t_vector		*position;
	t_vector		*target;
	t_vector		*up;
	t_matrix		*view_matrix;
	t_canvas		*canvas;
	t_rgb			*color;
	double			zoom;
}					t_camera;

typedef struct		s_scene
{
	t_camera		*camera;
	t_map			*map;
}					t_scene;

/*
** Input functions & serialization
*/
t_map				*serialize(char *filename);

/*
** Logging functions
*/
void				log_map(t_map *map);
void				log_error(char *str, char *strerror);

/*
** Event handling
*/
int					handle_key_events(int key, void *param);

/*
** Draw graphics
*/
void				draw(void *mlx, void *mlx_wdw, t_scene *scene);

/*
** Scene related functions
*/
t_camera			*new_camera(t_vector *position, t_vector *target, t_vector *up);
t_scene				*new_scene(t_map *map, t_camera *camera);

#endif