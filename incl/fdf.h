/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/08 15:37:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_HEIGHT 1080
# define VIEW_SIZE 1000

# define ZOOM_SPEED 0.5

# define ERR_INVALID_INPUT "Lines must "\
						"consist of spaces & numbers."
# define ERR_SERIALIZATION "Input serialization failed."
# define ERRNO_INVALID_INPUT 5

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libmatrix/libmatrix.h"

#define MOVE_SPEED 0.1

# define MAP_RED 0
# define MAP_GREEN 255
# define MAP_BLUE 0
# define MAP_COLOR ((MAP_RED & 255) << 16) | ((MAP_GREEN & 255) << 8 | (MAP_BLUE & 255))

# define X_MIN_LIMIT -100
# define X_MAX_LIMIT 100
# define Y_MIN_LIMIT -100
# define Y_MAX_LIMIT 100
# define Z_MIN_LIMIT -100
# define Z_MAX_LIMIT -1

# define Z_POS_INIT -100

typedef struct		s_map
{
	t_vector		**vertices;
	size_t			vertex_count;
	double			x_min;
	double			y_min;
	double			z_min;
	double			x_max;
	double			y_max;
	double			z_max;
	size_t			x;
	size_t			y;
	t_vector		*scale;
	t_vector		*center;
}					t_map;

typedef struct 		s_camera
{
	t_vector		*position;
	t_vector		*target;
	t_vector		*up;
	t_matrix		*view;
	t_matrix		*projection;
	t_matrix		*transform;
	t_canvas		*canvas;
	t_rgb			*color;
}					t_camera;

typedef struct		s_scene
{
	t_camera		*camera;
	t_map			*map;
	void			*mlx;
	void			*mlx_wdw;
}					t_scene;

typedef struct		s_line
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	yi;
	int	xi;
	int	p;
}					t_line;

/*
** Input functions & serialization
*/
t_map				*serialize(char *filename);

/*
** Logging functions
*/
int					log_map(t_map *map);
int					log_error(char *str, char *strerror);
int					log_perror(char *str);

/*
** Event handling
*/
int					handle_key_events(int key, void *param);

/*
** Draw graphics
*/
void				draw(t_scene *scene);

/*
** Line
*/
void				draw_line(t_vector *point1, t_vector *point2, int color, t_scene *scene);

/*
** Scene related functions
*/
t_scene				*new_scene(void *mlx, void *mlx_wdw, t_map *map);
t_camera			*new_camera(t_vector *position, t_vector *up, t_map *map);
t_matrix			*cam_transform(t_map *map, t_matrix *view,
						t_matrix *projection);

#endif