/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/30 18:59:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libmatrix/libmatrix.h"

# define ERRNO_IN 5
# define ERR_CENTER "Failed to center map & set vertices"
# define ERR_READ "Lines must consist of spaces & (+/-)numbers"
# define ERR_MAP "Empty x or y in map data"
# define ERR_ROWS "Length of row must be same on each row"

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
# define KEY_G 5
# define KEY_C 8
# define KEY_TAB 48
# define KEY_SHIFT 257

/*
** Color helpers
*/
# define CLAMP_0_255(color) (color > 255 ? 255 : color < 0 ? 0 : color)
# define ALPHA(a) ((a >> 24) & 255)
# define RED(r) ((r >> 16) & 255)
# define GREEN(g) ((g >> 8) & 255)
# define BLUE(b) (b & 255)
# define R(r) (CLAMP_0_255(r) & 255) << 16
# define G(g) (CLAMP_0_255(g) & 255) << 8
# define B(b) CLAMP_0_255(b) & 255
# define A(a) (CLAMP_0_255(a) & 255) << 24
# define COLOR(r, g, b, a) A(a) | R(r) | G(g) | B(b)
# define UI_COLOR COLOR(255, 255, 0, 255)
# define BACKGROUND_COLOR COLOR(0, 0, 0, 0)

/*
** Initial settings & enums.
** A world unit in map data is one pixel, let's scale them SCALE
*/
# define WIDTH 1920
# define HEIGHT 1080
# define ASPECT_RATIO WIDTH / HEIGHT
# define SCALE 200
# define ORTHOGRAPHIC 2
# define PERSPECTIVE 1

/*
** Map holds all necessary information of the input data
*/
typedef struct		s_map
{
	t_vector		**vertices;
	size_t			vertex_count;
	size_t			size;
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
	char			*name;
	int				col_r;
	int				col_g;
	int				col_b;
	int				col_a;
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
	t_map			**maps;
	t_vector		***axes;
	int				axis_len;
	int				map_index;
	int				map_count;
	void			*mlx;
	void			*mlx_wdw;
	void			*frame;
	char			*frame_buf;
	int				pixel_bits;
	int				line_bytes;
	int				pixel_endian;
	int				mouse_right_pressed;
	int				mouse_left_pressed;
	int				shift_pressed;
	int				mouse_x;
	int				mouse_y;
	int				show_guide;
	int				redraw;
	int				col_r;
	int				col_g;
	int				col_b;
	int				col_a;
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
typedef struct		s_edge
{
	t_vector		*point1;
	t_vector		*point2;
	int				color_start;
	int				color_end;
	t_scene			*scene;
}					t_edge;

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
** Camera
*/
t_camera			*new_camera(t_vector *position, t_vector *up, t_map *map);
t_matrix			*cam_transform(t_camera *camera);
void				set_transform(t_camera *camera);
int					turn_camera(t_camera *camera, double pitch, double yaw);
int					move_camera_forward(t_camera *camera, double amount);
int					strafe_camera(t_camera *camera, double amount);
int					zoom(t_camera *camera, int dir);
int					loop_perspective(t_camera *camera);
int					camera_free(t_camera *camera);

/*
** Scene
*/
t_vector			***axes(int axis_len);
int					free_axes(t_vector ***axes, int axis_len);
void				draw_axes_on_frame(t_scene *scene);
void				draw_map_on_frame(t_scene *scene);
int					init_scene(t_scene *scene, int map_i);
t_scene				*new_scene(void *mlx, void *mlx_wdw,
					t_map **maps);
double				init_zscale(t_map *map);

/*
** Line drawing
*/
void				connect_points(t_edge *edge);
void				connect_map_pts_with_gradient(t_edge *edge);
void				draw_line(t_edge *edge);
int					grad_color(int start, int end, double gradient_mul);
void				swap_points_in_edge(t_edge *edge);
double				gradient_multiplier(double *in_minmax, double *out_minmax,
					t_vector *point, t_map *map);

/*
** Map (Input reading, serialization & map functionality)
*/
int					rotate_map(t_map *map, int amount_x,
					int amount_y, int amount_z);
int					scale_map(t_map *map, double x, double y, double z);
int					shift_map_vertices(t_map *map);
int					set_map_info(t_map *map);
t_map				*serialize_map(char *filename);
int					reset_map(t_map *map);
int					switch_map(t_scene *scene, int dir);
double				z_shift(t_map *map);
int					read_z_from_digit(char **line);
t_vector			**reallocate_map_vertices(t_map *map);
int					init_vals_before_read(t_map *map);

/*
** UI
*/
t_map_info			*map_info(t_scene *scene);
void				free_map_info(t_map_info *map);
void				draw_paragraph(t_scene *scene, char *text, int xpos,
					int ypos);
void				draw_vector(t_scene *scene, t_vector *v,
					int xpos, int ypos);
void				draw_ui(t_scene *scene);

/*
** Draw
*/
int					draw(t_scene *scene);

/*
** Events
*/
int					handle_key_press(int key, void *param);
int					handle_key_release(int key, void *param);
int					handle_mouse_button_press(int key, int x, int y,
					void *param);
int					handle_mouse_button_release(int key, int x, int y,
					void *param);
int					handle_mouse_move(int x, int y, void *param);
int					handle_loop(void *params);
int					handle_exit_event(void);

/*
** Logging
*/
int					log_err(char *str, char *strerror);
int					log_perr(char *str);

#endif
