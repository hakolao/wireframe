/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/24 16:27:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define ASPECT_RATIO WINDOW_WIDTH / WINDOW_HEIGHT
# define VIEW_SIZE 500

/*
** A world unit in map data is one pixel, let's scale them by
*/
# define SCALE 200
# define ERR_INVALID_INPUT "Lines must consist of spaces & numbers."
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
# define KEY_Q 12
# define KEY_E 14
# define KEY_P 35
# define KEY_1 18
# define KEY_2 19
# define KEY_NUM_4 86
# define KEY_NUM_6 88
# define KEY_NUM_8 91
# define KEY_NUM_2 84
# define SCROLL_UP 5
# define SCROLL_DOWN 4
# define MOUSE_BUTTON_RIGHT 2
# define MOUSE_BUTTON_LEFT 1
# define KEY_R 15

/*
** These are used only for working from home...
** (different keycodes at school)
** # define HOME_KEY_ESC 65307
** # define HOME_KEY_LEFT 65361
** # define HOME_KEY_RIGHT 65363
** # define HOME_KEY_DOWN 65364
** # define HOME_KEY_UP 65362
** # define HOME_KEY_W 119
** # define HOME_KEY_A 97
** # define HOME_KEY_S 115
** # define HOME_KEY_D 100
** # define HOME_KEY_Q 113
** # define HOME_KEY_E 101
** # define HOME_KEY_P 112
** # define HOME_KEY_1 49
** # define HOME_KEY_2 50
** # define HOME_KEY_J 106
** # define HOME_KEY_K 107
** # define HOME_KEY_I 105
** # define HOME_KEY_M 109
** # define HOME_MINUS 45
** # define HOME_PLUS 61
*/

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libmatrix/libmatrix.h"

# define CLAMP_255(color) (color > 255 ? 255 : color)
# define RED(rgb) ((rgb >> 16) & 255)
# define BLUE(rgb) ((rgb >> 8) & 255)
# define GREEN(rgb) (rgb & 255)
# define COLOR(r, g, b) ((CLAMP_255(r) & 255) << 16) | ((CLAMP_255(g) & 255) << 8 | (CLAMP_255(b) & 255))
# define MAP_R 255
# define MAP_G 255
# define MAP_B 255
# define MAP_COLOR COLOR(MAP_R, MAP_G, MAP_B)
# define UI_COLOR COLOR(255, 255, 255)

# define Z_POS_INIT 0

# define ORTHOGRAPHIC 2
# define PERSPECTIVE 1

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
	size_t			z;
	t_matrix		*rotation;
	t_matrix		*reset_rotation;
	t_vector		*center;
}					t_map;

typedef struct		s_camera
{
	t_vector		*position;
	t_matrix		*world;
	t_matrix		*view;
	t_matrix		*projection;
	t_matrix		*transform;
	t_canvas		*canvas;
	double			pitch;
	double			yaw;
	int				perspective;
	t_matrix		*unit_scale;
}					t_camera;

typedef struct		s_scene
{
	t_camera		*camera;
	t_map			*map;
	void			*mlx;
	void			*mlx_wdw;
	int				mouse_right_pressed;
	int				mouse_left_pressed;
	int				mouse_x;
	int				mouse_y;
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

typedef struct		s_line_connect
{
	t_vector		*point1;
	t_vector		*point2;
	int				direction;
	int				color_start;
	int				color_end;
	t_scene			*scene;
}					t_line_connect;

/*
** Main.c
*/
int					reset_fdf(t_scene *scene);

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
** add int handle_key_events_home(int key, void *param), when working home;
*/
int					handle_key_events(int key, void *param);
int					handle_mouse_button_press(int key, int x, int y,
					void *param);
int					handle_mouse_button_release(int key, int x, int y,
					void *param);
int					handle_mouse_move(int x, int y, void *param);

/*
** Draw graphics
*/
int					draw(t_scene *scene);

/*
** UI
*/
void				draw_ui(t_scene *scene);

/*
** Line drawing
*/
void				draw_line(t_line_connect *line_connect);
void				swap_points_in_line_connect(t_line_connect *line_connect);

/*
** Scene related functions
*/
t_scene				*new_scene(void *mlx, void *mlx_wdw, t_map *map);
t_camera			*new_camera(t_vector *position, t_vector *up, t_map *map);
t_matrix			*cam_transform(t_camera *camera);
void				set_transform(t_camera *camera);

/*
** Map utils
*/
int					rotate_map(t_map *map, int amount_x,
					int amount_y, int amount_z);
int					scale_map_z(t_map *map, double amount);
int					center_and_set_map_vertices(t_list *vtx_lst, t_map *map);

/*
** Cam utils
*/
int					turn_camera(t_camera *camera, double pitch, double yaw);
int					move_camera_forward(t_camera *camera, double amount);
int					strafe_camera(t_camera *camera, double amount);
int					zoom(t_camera *camera, int dir);
int					loop_perspective(t_camera *camera);

/*
** Screen pt
*/
void				connect_points(t_line_connect *line_connect);
void				connect_map_pts_with_gradient(t_line_connect *line_connect,
					t_vector *point1, t_vector *point2);

/*
** Axes
*/
void				draw_axes(t_scene *scene);

#endif
