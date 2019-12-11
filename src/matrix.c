/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:54:44 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 19:24:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"


t_matrix4	new_matrix()
{
	t_matrix4	m;
	t_vec4		v;

	v.vec[0] = 0;
	v.vec[1] = 0;
	v.vec[2] = 0;
	v.vec[3] = 0;
	m.vecs[0] = v;
	m.vecs[1] = v;
	m.vecs[2] = v;
	m.vecs[3] = v;
	return (m);
}

t_matrix4	identity_matrix()
{
	t_matrix4	id_mat;
	int			i;
	
	id_mat = new_matrix();
	i = 0;
	while (i < 4)
	{
		id_mat.vecs[i].vec[i] = 1;
		i++;
	}
	return (id_mat);
}

t_matrix4	scale_matrix(t_matrix4 mat, double scale)
{
	t_matrix4	id_mat;
	int			i;

	id_mat = identity_matrix();
	i = 0;
	while (i < 4)
	{
		id_mat.vecs[i].vec[i] = scale;
		i++;
	}
	return (matrix_mul(mat, id_mat));
}

t_matrix4	matrix_add(t_matrix4 mat1, t_matrix4 mat2)
{
	t_matrix4	mat_out;
	t_vec4		v;
	
	v.vec[0] = mat1.vecs[0].vec[0] + mat2.vecs[0].vec[0];
	v.vec[1] = mat1.vecs[0].vec[1] + mat2.vecs[0].vec[1];
	v.vec[2] = mat1.vecs[0].vec[2] + mat2.vecs[0].vec[2];
	v.vec[3] = mat1.vecs[0].vec[3] + mat2.vecs[0].vec[3];
	mat_out.vecs[0] = v;
	v.vec[0] = mat1.vecs[1].vec[0] + mat2.vecs[1].vec[0];
	v.vec[1] = mat1.vecs[1].vec[1] + mat2.vecs[1].vec[1];
	v.vec[2] = mat1.vecs[1].vec[2] + mat2.vecs[1].vec[2];
	v.vec[3] = mat1.vecs[1].vec[3] + mat2.vecs[1].vec[3];
	mat_out.vecs[1] = v;
	v.vec[0] = mat1.vecs[2].vec[0] + mat2.vecs[2].vec[0];
	v.vec[1] = mat1.vecs[2].vec[1] + mat2.vecs[2].vec[1];
	v.vec[2] = mat1.vecs[2].vec[2] + mat2.vecs[2].vec[2];
	v.vec[3] = mat1.vecs[2].vec[3] + mat2.vecs[2].vec[3];
	mat_out.vecs[2] = v;
	v.vec[0] = mat1.vecs[3].vec[0] + mat2.vecs[3].vec[0];
	v.vec[1] = mat1.vecs[3].vec[1] + mat2.vecs[3].vec[1];
	v.vec[2] = mat1.vecs[3].vec[2] + mat2.vecs[3].vec[2];
	v.vec[3] = mat1.vecs[3].vec[3] + mat2.vecs[3].vec[3];
	mat_out.vecs[3] = v;
	return (mat_out);
}

t_matrix4	matrix_mul(t_matrix4 mat1, t_matrix4 mat2)
{
	double		m1[4][4];
	double		m2[4][4];
	double		res[4][4];
	int			i;
	int			j;
	int			k;
	t_matrix4	out_mat;
    
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m1[i][j] = mat1.vecs[i].vec[j];
			m2[i][j] = mat2.vecs[i].vec[j];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			res[i][j] = 0; 
			while (k < 4)
			{
				res[i][j] += m1[i][k] * m2[k][j]; 
				k++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out_mat.vecs[i].vec[j] = res[i][j];
			j++;
		}
		i++;
	}
	return (out_mat);
}

t_vec4		vec_mult_by_matrix(t_vec4 vec, t_matrix4 mat)
{
	t_vec4		out;
    
	out.vec[0] = vec.vec[0] * mat.vecs[0].vec[0] +
					vec.vec[1] * mat.vecs[0].vec[1] +
					vec.vec[2] * mat.vecs[0].vec[2] +
					vec.vec[3] * mat.vecs[0].vec[3];
	out.vec[1] = vec.vec[0] * mat.vecs[1].vec[0] +
					vec.vec[1] * mat.vecs[1].vec[1] +
					vec.vec[2] * mat.vecs[1].vec[2] +
					vec.vec[3] * mat.vecs[1].vec[3];
	out.vec[2] = vec.vec[0] * mat.vecs[2].vec[0] +
					vec.vec[1] * mat.vecs[2].vec[1] +
					vec.vec[2] * mat.vecs[2].vec[2] +
					vec.vec[3] * mat.vecs[2].vec[3];
	out.vec[3] = vec.vec[0] * mat.vecs[3].vec[0] +
					vec.vec[1] * mat.vecs[3].vec[1] +
					vec.vec[2] * mat.vecs[3].vec[2] +
					vec.vec[3] * mat.vecs[3].vec[3];
	return (out);
}
