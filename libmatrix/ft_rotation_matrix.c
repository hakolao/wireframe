/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:30:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/21 15:25:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static t_matrix		*rotation_around_x(int amount)
{
	t_matrix	*rotation;
	double		angle;

	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	VALUE_AT(rotation, 1, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 1) = sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	return (rotation);
}

static t_matrix		*rotation_around_y(int amount)
{
	t_matrix	*rotation;
	double		angle;

	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 2, 0) = sin(angle);
	VALUE_AT(rotation, 0, 2) = -sin(angle);
	VALUE_AT(rotation, 2, 2) = cos(angle);
	return (rotation);
}

static t_matrix		*rotation_around_z(int amount)
{
	t_matrix	*rotation;
	double		angle;

	angle = (M_PI / 180) * amount;
	if ((rotation = ft_matrix_id(4, 4)) == NULL)
		return (NULL);
	VALUE_AT(rotation, 0, 0) = cos(angle);
	VALUE_AT(rotation, 0, 1) = -sin(angle);
	VALUE_AT(rotation, 1, 0) = sin(angle);
	VALUE_AT(rotation, 1, 1) = cos(angle);
	return (rotation);
}

t_matrix			*ft_rotation_matrix(int angle_x, int angle_y, int angle_z)
{
	t_matrix	*rotation_x;
	t_matrix	*rotation_y;
	t_matrix	*rotation_z;
	t_matrix	*tmp;
	t_matrix	*res;

	if ((tmp = ft_matrix_new(4, 4)) == NULL ||
		(res = ft_matrix_new(4, 4)) == NULL ||
		(rotation_x = rotation_around_x(angle_x)) == NULL ||
		(rotation_y = rotation_around_y(angle_y)) == NULL ||
		(rotation_z = rotation_around_z(angle_z)) == NULL)
		return (NULL);
	if (ft_matrix_mul(rotation_x, rotation_y, tmp) == FALSE ||
		ft_matrix_mul(tmp, rotation_z, res) == FALSE)
		return (NULL);
	ft_matrix_free(rotation_x);
	ft_matrix_free(rotation_y);
	ft_matrix_free(rotation_z);
	ft_matrix_free(tmp);
	return (res);
}
