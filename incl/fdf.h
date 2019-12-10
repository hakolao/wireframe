/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/10 17:02:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024

# include <mlx.h>
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

#endif