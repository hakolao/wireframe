/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/25 18:36:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libmatrix/libmatrix.h"

/*
** Input reading errors
*/
# define ERR_INVALID_INPUT "Lines must consist of spaces & numbers."
# define ERR_SERIALIZATION "Input serialization failed."
# define ERRNO_INVALID_INPUT 5

/*
** Key codes for event listening
*/
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
# define KEY_NUM_PLUS 69
# define KEY_NUM_MINUS 78

/*
** Color helpers
*/
# define RED(r) ((r >> 16) & 255)
# define GREEN(g) ((g >> 8) & 255)
# define BLUE(b) (b & 255)
# define C(color) (color > 255 ? 255 : color)
# define COLOR(r, g, b) (C(r) & 255) << 16 | (C(g) & 255) << 8 | C(b) & 255
# define UI_COLOR COLOR(255, 255, 255)

/*
** Initial settings & enums.
** A world unit in map data is one pixel, let's scale them SCALE
*/
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define ASPECT_RATIO WINDOW_WIDTH / WINDOW_HEIGHT
# define SCALE 200
# define Z_POS_INIT 0
# define ORTHOGRAPHIC 2
# define PERSPECTIVE 1

/*
** Map holds all necessary information of the input data
*/
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
	t_matrix		*scale;
	t_matrix		*reset_scale;
	t_vector		*center;
}					t_map;

/*
** Camera contains information of camera & movement related
** matrices & vertices & other information.
*/
typedef struct		s_camera
{
	t_vector		*position;
	t_vector		*init_position;
	t_matrix		*view;
	t_matrix		*projection;
	t_matrix		*transform;
	t_canvas		*canvas;
	double			pitch;
	double			yaw;
	t_vector		*up;
	int				perspective;
	t_matrix		*unit_scale;
}					t_camera;

/*
** Scene contains all data the application needs inside its loop
*/
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

/*
** A Helper struct to contain line drawing calculation data.
*/
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
** A Helper struct to contain start & end colors for gradient
** calculations in line drawing.
*/
typedef struct		s_line_connect
{
	t_vector		*point1;
	t_vector		*point2;
	int				color_start;
	int				color_end;
	t_scene			*scene;
}					t_line_connect;

/*
** A Helper struct for map information to be drawn on the UI
*/
typedef struct		s_map_info
{
	char			*vertices;
	char			*x_min;
	char			*x_max;
	char			*y_min;
	char			*y_max;
	char			*z_min;
	char			*z_max;
}					t_map_info;

/*
** Main.c. init function can be used to reset the application state.
*/
int					init(t_scene *scene);

/*
** Input functions & serialization of map data into map struct
*/
t_map				*serialize(char *filename);

/*
** Logging functions mostly for errors
*/
int					log_error(char *str, char *strerror);
int					log_perror(char *str);

/*
** Event handling
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
** Draw UI
*/
void				draw_ui(t_scene *scene);

/*
** Line drawing helper functions
*/
void				draw_line(t_line_connect *line_connect);
int					grad_color(int start, int end, double gradient_mul);
void				swap_points_in_line_connect(t_line_connect *line_connect);
double				gradient_multiplier(double *in_minmax, double *out_minmax,
					t_vector *point, t_map *map);
int					map_color(double mul);

/*
** Scene related functions
*/
t_scene				*new_scene(void *mlx, void *mlx_wdw, t_map *map);
t_camera			*new_camera(t_vector *position, t_vector *up, t_map *map);
t_matrix			*cam_transform(t_camera *camera);
void				set_transform(t_camera *camera);

/*
** Map utils to handle manipulations to the map
*/
int					rotate_map(t_map *map, int amount_x,
					int amount_y, int amount_z);
int					scale_map(t_map *map, double x, double y, double z);
int					center_and_set_map_vertices(t_list *vtx_lst, t_map *map);
int					set_map_info(t_map *map);

/*
** Cam utils to handle camera manipulations
*/
int					turn_camera(t_camera *camera, double pitch, double yaw);
int					move_camera_forward(t_camera *camera, double amount);
int					strafe_camera(t_camera *camera, double amount);
int					zoom(t_camera *camera, int dir);
int					loop_perspective(t_camera *camera);

/*
** Screen pt to bring vertices into screen space
*/
void				connect_points(t_line_connect *line_connect);
void				connect_map_pts_with_gradient(t_line_connect *line_connect,
					t_vector *point1, t_vector *point2);

/*
** Axes to draw x, y and z axis to the screen
*/
void				draw_axes(t_scene *scene);

#endif
