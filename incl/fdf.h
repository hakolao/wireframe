/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 13:00:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define ERR_INVALID_INPUT "Lines must "\
						"consist of spaces & numbers."
# define ERR_SERIALIZATION "Input serialization failed."
# define ERRNO_INVALID_INPUT 5

# define KEY_ESC 53

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct		s_vertex
{
	int				x;
	int				y;
	int				z;
}					t_vertex;

typedef struct		s_map
{
	t_list			*vertices;
	int				vertex_count;
	int				x_max;
	int				y_max;
	int				z_max;
}					t_map;



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

#endif